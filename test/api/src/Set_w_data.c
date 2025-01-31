#include <api.h>

void Set_w_data_1_column_3_rows() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            },
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));
        test_assert(ecs_has(world, e + i, Velocity));

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, e + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_1_column_3_rows_w_entities() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        ecs_entity_t e = 5000 + i;
        test_assert(ecs_has(world, e, Position));
        Position *p = ecs_get_ptr(world, e, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_w_entities() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            },
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));
        test_assert(ecs_has(world, 5000 + i, Velocity));

        Position *p = ecs_get_ptr(world, 5000 + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, 5000 + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_1_column_3_rows_overwrite_entities() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    /* Write again */
    e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            }
        }
    });  

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        ecs_entity_t e = 5000 + i;
        test_assert(ecs_has(world, e, Position));

        Position *p = ecs_get_ptr(world, e, Position);
        test_assert(p != NULL);
        test_int(p->x, 30 + i);
        test_int(p->y, 40 + i);
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_overwrite_entities() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            },
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {50, 60},
                {51, 61},
                {52, 62}
            },
            (Velocity[]) {
                {70, 80},
                {71, 81},
                {72, 82}
            },
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));
        test_assert(ecs_has(world, 5000 + i, Velocity));

        Position *p = ecs_get_ptr(world, 5000 + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 50 + i);
        test_int(p->y, 60 + i);

        Velocity *v = ecs_get_ptr(world, 5000 + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 70 + i);
        test_int(v->y, 80 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_overwrite_different_order() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    /* Write again, in different order */
    e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5002, 5000, 5001},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {32, 42},
                {30, 40},
                {31, 41}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        ecs_entity_t e = 5000 + i;
        test_assert(ecs_has(world, e, Position));

        Position *p = ecs_get_ptr(world, e, Position);
        test_assert(p != NULL);

        test_int(p->x, 30 + i);
        test_int(p->y, 40 + i);
    }

    ecs_fini(world);
}

void Set_w_data_overwrite_different_type() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {50, 60},
                {51, 61},
                {52, 62}
            },
            (Velocity[]) {
                {70, 80},
                {71, 81},
                {72, 82}
            },
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));
        test_assert(ecs_has(world, 5000 + i, Velocity));

        Position *p = ecs_get_ptr(world, 5000 + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 50 + i);
        test_int(p->y, 60 + i);

        Velocity *v = ecs_get_ptr(world, 5000 + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 70 + i);
        test_int(v->y, 80 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_no_data() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_table_data_t data = {
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = NULL
    };

    ecs_entity_t e = ecs_set_w_data(world, &data);

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));
        test_assert(ecs_has(world, 5000 + i, Velocity));       
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_1_tag() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TAG(world, MyTag);
    ECS_TYPE(world, Type, Position, Velocity, MyTag);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 3,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Position), MyTag, ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            NULL,
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));
        test_assert(ecs_has(world, e + i, Velocity));

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, e + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_1_parent() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Parent, 0);
    ECS_TYPE(world, Type, Position, Velocity, CHILDOF | Parent);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 3,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Position), ECS_CHILDOF | Parent, ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            NULL,
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));
        test_assert(ecs_has(world, e + i, Velocity));
        test_assert(ecs_contains(world, Parent, e + i));

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, e + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_1_base() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, 0);
    ECS_TYPE(world, Type, Position, Velocity, INSTANCEOF | Base);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 3,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Position), ECS_INSTANCEOF | Base, ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            NULL,
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));
        test_assert(ecs_has(world, e + i, Velocity));
        test_assert(ecs_has(world, e + i, Base));

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, e + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_1_base_w_entities() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_ENTITY(world, Base, 0);
    ECS_TYPE(world, Type, Position, Velocity, INSTANCEOF | Base);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 3,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ECS_INSTANCEOF | Base, ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            NULL,
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        ecs_entity_t e = 5000 + i;
        test_assert(ecs_has(world, e, Position));
        test_assert(ecs_has(world, e, Velocity));
        test_assert(ecs_has(world, e, Base));

        Position *p = ecs_get_ptr(world, e, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, e, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}


void Set_w_data_2_columns_3_rows_1_nested_prefab() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_PREFAB(world, MyPrefab, 0);
        ECS_PREFAB(world, PrefabChild, 0);
            ecs_set(world, PrefabChild, EcsPrefab, {.parent = MyPrefab});

    ECS_TYPE(world, Type, Position, Velocity, INSTANCEOF | MyPrefab);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 3,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Position), ECS_INSTANCEOF | MyPrefab, ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            NULL,
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));
        test_assert(ecs_has(world, e + i, Velocity));
        test_assert(ecs_has(world, e + i, MyPrefab));

        ecs_entity_t child = ecs_lookup_child(world, e + i, "PrefabChild");   
        test_assert(child != 0);

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, e + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_2_columns_3_rows_component_order() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 3,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Velocity), ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            },
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}                
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));
        test_assert(ecs_has(world, e + i, Velocity));

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, e + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_overwrite_w_unset_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            (Velocity[]) {
                {30, 40},
                {31, 41},
                {32, 42}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {50, 60},
                {51, 61},
                {52, 62}
            },
            NULL
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));
        test_assert(ecs_has(world, 5000 + i, Velocity));

        Position *p = ecs_get_ptr(world, 5000 + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 50 + i);
        test_int(p->y, 60 + i);

        Velocity *v = ecs_get_ptr(world, 5000 + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 30 + i);
        test_int(v->y, 40 + i);        
    }

    ecs_fini(world);
}

void Set_w_data_overwrite_from_other_type_w_unset_column() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);

    e = ecs_set_w_data(world, &(ecs_table_data_t){
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ecs_entity(Velocity)},
        .columns = (ecs_table_columns_t[]){
            NULL,
            (Velocity[]) {
                {70, 80},
                {71, 81},
                {72, 82}
            },
        }
    });

    test_assert(e != 0);
    test_int(ecs_count(world, Position), 3);
    test_int(ecs_count(world, Type), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));
        test_assert(ecs_has(world, 5000 + i, Velocity));

        Position *p = ecs_get_ptr(world, 5000 + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);

        Velocity *v = ecs_get_ptr(world, 5000 + i, Velocity);
        test_assert(v != NULL);
        test_int(v->x, 70 + i);
        test_int(v->y, 80 + i);        
    }

    ecs_fini(world);
}

static ecs_entity_t e_result;

static
void Set_w_data(ecs_rows_t *rows) {
    ecs_table_data_t *data = ecs_get_context(rows->world);
    ecs_entity_t e = ecs_set_w_data(rows->world, data);
    test_assert(e != 0);

    e_result = e;
}

void Set_w_data_staged_1_column_3_rows() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, Set_w_data, EcsOnUpdate, .Position);

    ecs_table_data_t data = {
        .column_count = 1,
        .row_count = 3,
        .entities = NULL,
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    };

    ecs_set_context(world, &data);

    ecs_progress(world, 1);
    test_int(ecs_count(world, Position), 3);

    ecs_entity_t e = e_result;

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, e + i, Position));

        Position *p = ecs_get_ptr(world, e + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);
    }

    ecs_fini(world);
}

void Set_w_data_staged_1_column_3_rows_w_entities() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, Set_w_data, EcsOnUpdate, .Position);

    ecs_table_data_t data = {
        .column_count = 1,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position)},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            }
        }
    };

    ecs_set_context(world, &data);

    ecs_progress(world, 1);
    test_int(ecs_count(world, Position), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));

        Position *p = ecs_get_ptr(world, 5000 + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);
    }

    ecs_fini(world);
}

void Set_w_data_staged_1_column_3_rows_w_entities_w_base() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, Set_w_data, EcsOnUpdate, .Position);
    ECS_ENTITY(world, Base, 0);

    ecs_table_data_t data = {
        .column_count = 2,
        .row_count = 3,
        .entities = (ecs_entity_t[]){5000, 5001, 5002},
        .components = (ecs_entity_t[]){ecs_entity(Position), ECS_INSTANCEOF | Base},
        .columns = (ecs_table_columns_t[]){
            (Position[]) {
                {10, 20},
                {11, 21},
                {12, 22}
            },
            NULL
        }
    };

    ecs_set_context(world, &data);

    ecs_progress(world, 1);
    test_int(ecs_count(world, Position), 3);

    int i;
    for (i = 0; i < 3; i ++) {
        test_assert(ecs_has(world, 5000 + i, Position));

        Position *p = ecs_get_ptr(world, 5000 + i, Position);
        test_assert(p != NULL);
        test_int(p->x, 10 + i);
        test_int(p->y, 20 + i);
    }

    ecs_fini(world);
}
