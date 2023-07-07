#include "mesh_renderer.h"
#include "../world/chunk/chunklet.h"

MeshRenderer::MeshRenderer()
{


}


MeshRenderer::~MeshRenderer()
{

}


void MeshRenderer::AddMesh(RenderInfo *mesh) {
    meshes_.push_back(mesh);
}


void MeshRenderer::AddReferenceMesh(void) {
    Mesh *test_mesh = new Mesh();
    std::vector<Vertex> vertices = {

            //front
            {{-1.0f, -1.0f, 1.0f},  {0.0f,  0.0f,  1.0},  {1.0f, 0.0f, 0.0}, {0.0, 1.0}},
            {{-1.0f, 1.0f,  1.0f},  {0.0f,  0.0f,  1.0},  {0.0f, 1.0f, 0.0}, {0.0, 0.0}},
            {{1.0f,  1.0f,  1.0f},  {0.0f,  0.0f,  1.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}},
            {{1.0f,  -1.0f, 1.0f},  {0.0f,  0.0f,  1.0},  {1.0f, 0.0f, 1.0}, {1.0, 1.0}},

            // back
            {{1.0,   -1.0,  -1.0},  {0.0f,  0.0f,  -1.0}, {1.0f, 0.0f, 1.0}, {0.0, 1.0}}, //4
            {{1.0f,  1.0,   -1.0},  {0.0f,  0.0f,  -1.0}, {0.0f, 1.0f, 1.0}, {0.0, 0.0}}, //5
            {{-1.0,  1.0,   -1.0},  {0.0f,  0.0f,  -1.0}, {0.0f, 1.0f, 1.0}, {1.0, 0.0}}, //6
            {{-1.0,  -1.0,  -1.0},  {0.0f,  0.0f,  -1.0}, {1.0f, 0.0f, 1.0}, {1.0, 1.0}}, //7


            //left
            {{-1.0,  -1.0,  -1.0},  {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, //8
            {{-1.0f, 1.0,   -1.0},  {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //9
            {{-1.0,  1.0,   1.0},   {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}},   //10
            {{-1.0,  -1.0,  1.0},   {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //11

            //right
            {{1.0,   -1.0,  1.0},   {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, // 12
            {{1.0f,  1.0,   1.0},   {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //13
            {{1.0,   1.0,   -1.0},  {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}}, //14
            {{1.0,   -1.0,  -1.0},  {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //15

            //top
            {{-1.0f, 1.0f,  1.0f},  {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, //16
            {{-1.0f, 1.0f,  -1.0f}, {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //17
            {{1.0f,  1.0f,  -1.0f}, {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}}, //18
            {{1.0f,  1.0f,  1.0f},  {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //19

            //bottom
            {{-1.0f, -1.0,  -1.0},  {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, //20
            {{-1.0,  -1.0,  1.0},   {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //21
            {{1.0,   -1.0,  1.0},   {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}},  //22
            {{1.0,   -1.0,  -1.0},  {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //23

    };

    std::vector<uint32_t> indices = {

            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            4, 6, 7,

            8, 9, 10,
            8, 10, 11,

            12, 13, 14,
            12, 14, 15,

            16, 17, 18,
            16, 18, 19,

            20, 21, 22,
            20, 22, 23

    };


    test_mesh->vertices.clear();
    test_mesh->indices.clear();
    test_mesh->vertices = vertices;
    test_mesh->indices = indices;
    std::cout << test_mesh->vertices.size() << std::endl;
    std::cout << test_mesh->indices.size() << std::endl;

    glGenVertexArrays(1, &test_mesh->render_info.vao);
    glBindVertexArray(test_mesh->render_info.vao);

    glGenBuffers(1, &test_mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, test_mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * test_mesh->vertices.size(), &test_mesh->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &test_mesh->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * test_mesh->indices.size(), &test_mesh->indices[0],
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (offsetof(Vertex, Vertex::tex_coords)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    AddMesh(&test_mesh->render_info);
}


void MeshRenderer::Render(Camera &camera) {
    u32 vp_loc = glGetUniformLocation(shader_, "vp");

    glUseProgram(shader_);
    glUniformMatrix4fv(vp_loc, 1, GL_FALSE, camera.GetViewProjValuePtr());
    glBindTexture(GL_TEXTURE_2D, texture_);

    for (const auto &mesh: meshes_) {
        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, mesh->faces * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    meshes_.clear();
}

void MeshRenderer::SetTexture(u32 texture) {
    texture_ = texture;
}

void MeshRenderer::SetShader(u32 shader) {
    shader_ = shader;
}
