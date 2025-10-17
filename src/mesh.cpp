#define _MY_OPENGL_IS_33_

#include "mesh.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

void Mesh::setPositions(const std::vector<float>& pos) { m_pos = pos; }
void Mesh::setColors(const std::vector<float>& col) { m_col = col; }
void Mesh::setIndices(const std::vector<unsigned int>& idx) { m_idx = idx; }
void Mesh::setNormals(const std::vector<float>& nrm) {m_nrm = nrm;}
void Mesh::setTextureCoordinates(const std::vector<float>& uv) {m_uv = uv;}

void Mesh::upload() {
  
  assert((m_pos.size() % 3) == 0);
  if (!m_col.empty()) assert(m_col.size() == m_pos.size());
  if (!m_nrm.empty()) assert(m_nrm.size() == m_pos.size());
  assert(!m_idx.empty());

#ifdef _MY_OPENGL_IS_33_
  
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  
  glGenBuffers(1, &m_vboPos);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * m_pos.size(),
               m_pos.data(),
               GL_DYNAMIC_READ);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  
  if (!m_col.empty()) {
    glGenBuffers(1, &m_vboCol);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboCol);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * m_col.size(),
                 m_col.data(),
                 GL_DYNAMIC_READ);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
  }

  if (!m_nrm.empty()) {
    glGenBuffers(1, &m_vboNrm);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboNrm);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * m_nrm.size(),
                 m_nrm.data(),
                 GL_DYNAMIC_READ);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(2);
  }

  if (!m_uv.empty()) {
    glGenBuffers(1, &m_vboUV);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboUV);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * m_uv.size(),
                 m_uv.data(),
                 GL_DYNAMIC_READ);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(3);
  }

  
  glGenBuffers(1, &m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * m_idx.size(),
               m_idx.data(),
               GL_DYNAMIC_READ);
#endif

  glBindVertexArray(0);
}

void Mesh::buildSphere(int stacks, int slices){
  m_pos.clear();
  m_nrm.clear();
  m_idx.clear();

  for(int i = 0; i <= stacks; i++){
    float phi = M_PI * i / stacks;
    float y = std::cos(phi);
    float r = std::sin(phi);

    for (int j = 0; j <= slices; j++){
      float theta = 2.f * M_PI * j / slices;
      float x = r * std::cos(theta);
      float z = r * std::sin(theta);

      m_pos.insert(m_pos.end(), {x, y, z});
      m_nrm.insert(m_nrm.end(), {x, y, z});

      float u = (float)j/slices;
      float v = (float)i/stacks;
      m_uv.insert(m_uv.end(), {u, v});

    }
  }

  for(int i = 0; i < stacks; i++){
    for(int j = 0; j < slices; j++){
      unsigned int first = i * (slices + 1) + j;
      unsigned int second = first + slices + 1;

      m_idx.insert(m_idx.end(), {first, second, first + 1});
      m_idx.insert(m_idx.end(), {second, second + 1, first + 1});
    }
  }

  

}

void Mesh::render() const {
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_idx.size()), GL_UNSIGNED_INT, (void*)0);
  glBindVertexArray(0);
}

void Mesh::destroy() {
  if (m_ibo)    { glDeleteBuffers(1, &m_ibo);    m_ibo = 0; }
  if (m_vboCol) { glDeleteBuffers(1, &m_vboCol); m_vboCol = 0; }
  if (m_vboPos) { glDeleteBuffers(1, &m_vboPos); m_vboPos = 0; }
  if (m_vao)    { glDeleteVertexArrays(1, &m_vao); m_vao = 0; }
  if (m_vboNrm) { glDeleteBuffers(1, &m_vboNrm); m_vboNrm = 0;}
}