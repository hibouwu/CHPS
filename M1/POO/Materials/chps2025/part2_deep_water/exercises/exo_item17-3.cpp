#include <iostream>
#include <memory>

class Face{
public:
  int id = -1;
  ~Face() {std::cout << "Delete Face"<< std::endl;}
};

class CellUniqueFace{
public:
  int m_face_id = -1;
  std::unique_ptr<Face> m_face = std::make_unique<Face>(m_face_id);
  ~CellUniqueFace() {std::cout << "Delete Cell"<< std::endl;}
};

class CellSharedFace{
public:
  int m_face_id = -1;
  std::shared_ptr<Face> m_face = std::make_shared<Face>(m_face_id);
  ~CellSharedFace() {std::cout << "Delete Cell"<< std::endl;}
};

void printFace(Face const& face){
std::cout << "Face id "<< face.id << std::endl;
}

void printFaceWeakPtrIfPossible(std::weak_ptr<Face> face_weak_ptr){
  if (! face_weak_ptr.expired()) {
    auto face_shared_ptr = face_weak_ptr.lock();
    printFace(*face_shared_ptr);
  }
  else std::cout << "Face weak ptr expired"<<std::endl;
}

void testUniquePtr(){
  std::cout << "== Test unique ptr " << std::endl;
  CellUniqueFace c2;
  {
    CellUniqueFace c{1};
    printFace(*c.m_face);
    c2.m_face = std::move(c.m_face);
  }
  printFace(*c2.m_face);
}

void testSharedPtr(){
  std::cout << "== Test shared ptr " << std::endl;
  std::shared_ptr<Face> face = nullptr;
  {
    CellSharedFace cell{1};
    face = cell.m_face;
    printFace(*face);
  }
  printFace(*face);
}

void testWeakPtr(){
  std::cout << "== Test shared ptr " << std::endl;
  std::weak_ptr<Face> face;
  {
    CellSharedFace cell{1};
    face = cell.m_face;
    printFaceWeakPtrIfPossible(face);
  }
  printFaceWeakPtrIfPossible(face);
}

int main() {

  testUniquePtr();
  testSharedPtr();
  testWeakPtr();
 
  return 0;
} // refaire avec weak