#pragma once
#include<GL/glut.h>
#include<iostream>
#include"stb_image.h"

namespace texture{
  class Texture{
    public:
      Texture() {
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      }
      Texture(const char* filename){
        load(filename);
      }
      void load(const char* filename) {
        glEnable(GL_TEXTURE_2D);
        int width, height, nrChannels;
        unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
        if (data)
        {
          glGenTextures(1, &texture);
          glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
          glBindTexture(GL_TEXTURE_2D, texture);
          glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
          }
          else
          {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
          }
          glGenerateMipmap(GL_TEXTURE_2D);
          std::cout << "texture loaded" << std::endl;
          glBindTexture(GL_TEXTURE_2D, 0);
          // glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
          // glBindTexture(GL_TEXTURE_2D, texture);
          // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          // if (nrChannels == 1)
          //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
          // else if (nrChannels == 3)
          //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
          // else if (nrChannels == 4)
          //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
          // glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
          std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        glDisable(GL_TEXTURE_2D);
      }
      // int t = 0;
      void bind(){
        glBindTexture(GL_TEXTURE_2D, texture);
      }
      void unbind() {
        // std::cout << t++ << std::endl;
        glBindTexture(GL_TEXTURE_2D, 0);
      }
    private:
      unsigned int texture;
  };
}