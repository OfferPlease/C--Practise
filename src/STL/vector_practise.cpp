#include <iostream>
#include <vector>
// std:: standard template library
// the data type the containers contains is provided by users
// vector memory is inline in memory, continuous in memory, convenient for iteration
struct Vertex
{
    float x, y, z;
    // write a copy consturctor for better memory allocation when resizing vectors
    Vertex(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vertex(const Vertex& vertex)
    : x(vertex.x), y(vertex.y), z(vertex.z)
    {
        std::cout<<"vertex copyied!"<<std::endl;
    }
};
int main() {
    std::vector<Vertex> vertices;
    // tell the vertex that we will put in 3 vertices, it should keep room for 3 vertices
    vertices.reserve(6);
    std::vector<int> nums; // can store primitive types in std vector
    // add items to vector
    // these Vertex objects are constructed on stack and copied to heap
    // vertices.push_back(Vertex(1,2,3));
    // vertices.push_back(Vertex(4,5,6));
    // vertices.push_back(Vertex(7,8,9));
    // to aviod copy and directly create Vector objects on heap, use embrace_back and directly pass in the parameters for the constructor
    vertices.emplace_back(1,2,3);
    vertices.emplace_back(4,5,6);
    vertices.emplace_back(7,8,9);
    // interate a vector
    for(int i=0; i<vertices.size(); i++)
    {
        std::cout << vertices[i].x <<vertices[i].y<<vertices[i].z<< std::endl;
    }
    for(Vertex& v: vertices) // make a reference, avoid copy
    {
        std::cout << v.x << v.y << v.z << std::endl;
    }
    // remove a specific element (need to pass in a iterator)
    // remove the second element
    // vertices.begin() : the first element in the vector


    vertices.erase(vertices.begin()+1);
    // clear the vector, resize the size back to 0
    //vertices.clear()

    /* optimaiza vector behaviour, avoid copying：write a copy constructor for the Vertex class */
    return 0;
}
