#pragma once
#include<GL/glut.h>
namespace paint{
    class paints {
        public:
            paints() {
                // TODO
            }
            virtual void draw(int height, int width) = 0;
            // virtual string get_id() = 0;
            virtual void insert(int x, int y) = 0;
            virtual void clear() = 0;
            virtual void set_mode(int mode) = 0;
            virtual void set_color(float r, float g, float b) = 0;
            virtual void set_width(float width) = 0;
            virtual paints* clone() const = 0;
    };
}