#include "add.h"

int *add_1_svc(numbers *num, struct svc_req *req) {
    static int result;
    result = num->a + num->b;
    return &result;
}
