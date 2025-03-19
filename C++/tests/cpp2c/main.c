#include <stdio.h>

enum Color_ColorEnum { COLOR_RED, COLOR_GREEN, COLOR_DEFAULT };
void Color_setColor(Color_ColorEnum color) {		
	static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
	puts(pallete[color]);
}

struct Scalable;
struct Scaleable_vtbl {
    void (*dtor)(struct Scalable*);
    void (*scale)(struct Scalable*, double f);
};

struct Scalable {
    struct Scaleable_vtbl* vptr;
};

void Scalable_dtor(struct Scalable* self) {
    // body
    
    // dtor members
    self->vptr = 0;
    // base dtor
}


void Scalable_scale(struct Scalable* self, double f) {
    puts("pure function call");
    abort();
}

struct Scalable_vtbl __scalable_vtbl = {
    &Scalable_dtor,
    &Scalable_scale
};

void Scalable_ctor(struct Scalable* self) {
    //  base ctor
    // mil
    self->vptr = &__scalable_vtbl;
    // body
}

PF __shape_vtbl[] = {
    (PF)&Shape_dtor,
    (PF)&Shape_draw,
    (PF)&Shape_draw_ccen;
    (PF)&Shape_scale_d,
    (PF)&Shape_area
};

struct Shape {
    PF* vptr;
    int m_id;
};

int Shape_NumOFShapes = 0;

typedef void* (*PF)(void*);



void Shape_ctor(struct Shape* self) {
    Scalable_ctor((struct Scalable*)self);

    self->vptr = &__shape_vtbl[0];
    self->m_id = ++Shape_NumOFShapes;

    printf("Shape::CTOR - %d\n", self->m_id);
}


void test(struct Scalable* s, struct Shape* shp) {
    //Scalable_work(s, 2, 3);
    s->vptr->scale(s, 2.5);

    (shp->vptr[1])(shp, 2.5)
    (void ())(**shp+1)(shp, 2.5)
}



int main () {
    for(int i = 0; i < 10; ++i) {
        printf("%d", i);
    }

        printf("%d", i);

}