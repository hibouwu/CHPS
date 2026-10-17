#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_CUBIN_HANDLE_STORAGE__ static
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "tp1_check.fatbin.c"
extern void __device_stub__Z6kernelPi(int *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z6kernelPi(int *__par0){__cudaLaunchPrologue(1);__cudaSetupArgSimple(__par0, 0UL);__cudaLaunch(((char *)((void ( *)(int *))kernel)));}
# 20 "Partie1/tp1_check.cu"
void kernel( int *__cuda_0)
# 21 "Partie1/tp1_check.cu"
{__device_stub__Z6kernelPi( __cuda_0);

}
# 1 "/gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009/RESULTS/romeo-738578/CUDAIMG/tp1_check.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T2) {  __nv_dummy_param_ref(__T2); __nv_save_fatbinhandle_for_managed_rt(__T2); __cudaRegisterEntry(__T2, ((void ( *)(int *))kernel), _Z6kernelPi, (-1)); }
static void __sti____cudaRegisterAll(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
