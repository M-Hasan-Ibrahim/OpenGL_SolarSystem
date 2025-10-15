#pragma once
#include <glad/gl.h>
#include <vector>

class Mesh {
public:
  
  void setPositions(const std::vector<float>& pos);      
  void setColors(const std::vector<float>& col);         
  void setIndices(const std::vector<unsigned int>& idx);

  void setNormals(const std::vector<float>& nrm);
  void buildSphere(int stacks = 30, int slices = 30);


  void upload();    
  void render() const;
  void destroy();  

private:
  
  std::vector<float> m_pos;
  std::vector<float> m_col;
  std::vector<unsigned int> m_idx;

  std::vector<float> m_nrm;

  
  GLuint m_vao = 0;
  GLuint m_vboPos = 0;
  GLuint m_vboCol = 0;
  GLuint m_ibo = 0;

  GLuint m_vboNrm = 0;
};