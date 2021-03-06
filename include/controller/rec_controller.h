#ifndef _REC_CONTROLLER_H
#define _REC_CONTROLLER_H

#include "controller/controller.h"
#include "utils/hashmap.h"

void rec_controller_create(controller *ctrl, int player, sd_rec_file *rec);
void rec_controller_free(controller *ctrl);

#endif // _REC_CONTROLLER_H
