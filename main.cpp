#include "Decorator.h"

int main() {
    /* Инициализируем простую сетку */
    IMesh* basicMesh = new RegularMesh;
    std::cout << basicMesh->addMeshProperties() << std::endl;
    /* А теперь будем её декорировать текстурами и цветами */
    basicMesh = new Texture(basicMesh, "Stone");
    basicMesh = new Color(basicMesh, "Red");
    std::cout << basicMesh->addMeshProperties() << std::endl;
    /* Наложим еще одну эффект и шейдер */
    basicMesh = new Effect(basicMesh, "Ice");
    basicMesh = new Shader(basicMesh, "Sun");
    std::cout << basicMesh->addMeshProperties() << std::endl;
    delete basicMesh;
    return 0;
}
