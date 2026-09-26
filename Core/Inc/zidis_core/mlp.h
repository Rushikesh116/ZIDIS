#ifndef ZIDIS_CORE_MLP_H
#define ZIDIS_CORE_MLP_H

#include "config.h"
#include "dsp.h"

void Mlp_Init(void);
EventClass_t Mlp_Classify(const ZidisFeatures_t *features, float *out_confidence);

#endif // ZIDIS_CORE_MLP_H
