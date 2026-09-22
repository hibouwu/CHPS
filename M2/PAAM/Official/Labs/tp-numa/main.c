#include <hwloc.h>
#include <stdio.h>
#include <stdbool.h>

hwloc_topology_t topology;

struct node {
  hwloc_obj_t obj;
  struct pu* pus;
  size_t nb_pus;
};

struct pu {
  hwloc_obj_t obj;
  struct node* node;
};

struct topology {
  size_t nb_nodes;
  size_t nb_pus;
  struct pu* pus;
  struct node* nodes;
}* numa;

void print_obj(hwloc_obj_t obj, char* prefix, bool verbose) {
  char type[32];
  char attributes[256];
    
  // Récupérer le type de l'objet
  hwloc_obj_type_snprintf(type, sizeof(type), obj, 0);
    
  // Récupérer les attributs de l'objet
  hwloc_obj_attr_snprintf(attributes, sizeof(attributes), obj, " ", 0);
    
  // Afficher les informations de l'objet
  if(verbose) {
    printf("%sObject@%p\n", prefix, obj);
    printf("%s  Object Type: %s\n", prefix, type);
    printf("%s  OS Index: %d\n", prefix, obj->os_index);
    printf("%s  Attributes: %s\n", prefix, attributes);
    printf("%s  Depth: %d\n", prefix, obj->depth);
    printf("%s  Logical Index: %d\n", prefix, obj->logical_index);
    printf("%s  Number of Children: %u\n", prefix, obj->arity);
  } else
    printf("%s%s at index %d\n", prefix, type, obj->logical_index);
}

hwloc_obj_t is_ancestor(hwloc_obj_t base, hwloc_obj_t obj) {
  for(hwloc_obj_t cur=obj; cur; cur=cur->parent)
    if(cur == base)
      return cur;
  return NULL;
}

void extract_numa_topology() {
  // To understand the topology, you can take a look at the page here: https://www.open-mpi.org/projects/hwloc/doc/v2.2.0/a00325.php
  numa = malloc(sizeof(*numa));

  // allocate the space for the nodes
  int depth_numa = hwloc_get_type_depth(topology, HWLOC_OBJ_NUMANODE);

  numa->nb_nodes = hwloc_get_nbobjs_by_depth(topology, depth_numa);
  numa->nodes = malloc(sizeof(*numa->nodes)*numa->nb_nodes);
  
  // record the numa nodes
  hwloc_obj_t obj = NULL;
  size_t n = 0;
  while ((obj = hwloc_get_next_obj_by_type(topology, HWLOC_OBJ_NUMANODE, obj)) != NULL) {
    numa->nodes[n].obj = obj;
    numa->nodes[n].nb_pus = 0;
    n++;
  }
  
  // allocate the space for the cpus
  int depth_pu = hwloc_get_type_depth(topology, HWLOC_OBJ_PU);

  numa->nb_pus = hwloc_get_nbobjs_by_depth(topology, depth_pu);
  numa->pus = malloc(sizeof(*numa->pus)*numa->nb_pus);

  // record the cpus and associates them to the nodes
  obj = NULL;
  n = 0;
  while ((obj = hwloc_get_next_obj_by_type(topology, HWLOC_OBJ_PU, obj)) != NULL) {
    numa->pus[n].obj = obj;
    
    for(size_t i=0; i<numa->nb_nodes; i++)
      if(is_ancestor(numa->nodes[i].obj->parent, numa->pus[n].obj)) {
        numa->pus[n].node = &numa->nodes[i];
        numa->pus[n].node->nb_pus++;
      }
    
    n++;
  }

  // build the invert tree
  for(size_t i=0; i<numa->nb_nodes; i++) {
    numa->nodes[i].pus = malloc(sizeof(*numa->nodes[i].pus)*numa->nodes[i].nb_pus);
    numa->nodes[i].nb_pus = 0;
  }

  for(size_t i=0; i<numa->nb_pus; i++) {
    struct node* node = numa->pus[i].node;
    node->pus[node->nb_pus++] = numa->pus[i];
  }
}

void print_numa_topology() {
  for(size_t i=0; i<numa->nb_nodes; i++) {
    print_obj(numa->nodes[i].obj, "", 0);
    for(size_t j=0; j<numa->nodes[i].nb_pus; j++)
      print_obj(numa->nodes[i].pus[j].obj, "  ", 0);
  }
}

int main(int argc, char* argv[]) {
  // Initialize topology
  hwloc_topology_init(&topology);
  hwloc_topology_set_flags(topology, HWLOC_TOPOLOGY_FLAG_WHOLE_SYSTEM);
  hwloc_topology_load(topology);

  extract_numa_topology();
  print_numa_topology();

  hwloc_set_cpubind(topology, numa->pus[0].obj->cpuset, HWLOC_CPUBIND_THREAD);

  char* buf = hwloc_alloc_membind(topology,
                                  32 * 1024 * 1024,
                                  numa->pus[0].node->obj->nodeset,
                                  HWLOC_MEMBIND_BIND,
                                  HWLOC_MEMBIND_STRICT | HWLOC_MEMBIND_BYNODESET | HWLOC_MEMBIND_NOCPUBIND );

  printf("=> %p\n", buf);
  
  // cleanup
  hwloc_topology_destroy(topology);
  return 0;
};
