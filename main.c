#include "m_pd.h"
#include <math.h>

static t_float scales[2][12] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9742}, //Rast
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static t_class *djemil_class;

typedef struct _djemil {
    t_object    x_obj;
    t_outlet    *f_out;
    t_float     freq, sclNo;
    t_int       fret;
}t_djemil;


void djemil_setMaqam(t_djemil *x, t_symbol *s, t_int argc, t_atom *argv) {

    if (argv[0].a_type != A_SYMBOL) return;

    if (atom_getsymbol(argv) == gensym("Rast") || atom_getsymbol(argv) == gensym("rast")) {
        post("Set to maqam Rast");
        x->sclNo = 0;
    }
}

void djemil_process(t_djemil *x, t_float f) {

            x->fret = (t_int) f % 12;
            x->freq = mtof(f)*scales[(t_int)x->sclNo][(t_int)x->fret];
            //post("Note = %d", x->fret);
            outlet_float(x->x_obj.ob_outlet, x->freq);
}



void *djemil_new(void){

    t_djemil *x = (t_djemil *)pd_new(djemil_class);
    x->f_out = outlet_new(&x->x_obj, &s_float);
    return (void *)x;
}


void djemil_setup(void) {

    djemil_class = class_new(gensym("djemil"),
                    (t_newmethod)djemil_new,
                     0, sizeof(t_djemil),
                     CLASS_DEFAULT, 0);

    class_addfloat(djemil_class, (t_method) djemil_process);

    class_addmethod(djemil_class, (t_method) djemil_setMaqam,
                    gensym("set"), A_GIMME, 0);
}
