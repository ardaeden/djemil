#include "m_pd.h"
#include <math.h>


static t_class *djemil_class;

typedef struct _djemil {
    t_object    x_obj;

}t_djemil;


void djemil_set(t_djemil *x, t_floatarg f) {

post("Set message received with %d", f);
}

void *djemil_new(void){
    t_djemil *x = (t_djemil *)pd_new(djemil_class);
    //outlet_new(x, &s_float);
    return (void *)x;
}


void djemil_setup(void) {
    djemil_class = class_new(gensym("djemil"),
    (t_newmethod)djemil_new,
    0, sizeof(t_djemil),
    CLASS_DEFAULT, 0);
    class_addmethod(djemil_class,
                    (t_method)djemil_set,
                    gensym("set"), A_DEFFLOAT, 0);

}
