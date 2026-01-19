#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdint.h>
#include <stddef.h>

/* ---------- Fixed-point Q16.16 ---------- */
typedef int32_t fx16_t;

#define FX16_ONE          ((fx16_t)0x00010000)
#define FX16_FROM_INT(x)  ((fx16_t)((x) << 16))
#define FX16_TO_INT(x)    ((int32_t)((x) >> 16))

/* ---------- Bullet physics state ---------- */
typedef struct {
    fx16_t x, y;
    fx16_t vx, vy;
} PhysBullet_t;

/* ---------- Lorentz parameters ---------- */
typedef struct {
    fx16_t k;          // curvature strength (q/m)
    fx16_t B0;         // base field strength
    fx16_t Bmax;       // clamp field
    fx16_t vmax;       // velocity clamp

    int32_t soft2;     // softening (px^2)
    int32_t range2;    // activation range^2
    int32_t radius;   // asteroid radius (px)
    int32_t edge;     // edge thickness (px)
} LorentzParams_t;

/* ---------- API ---------- */
LorentzParams_t lorentz_defaults(void);

PhysBullet_t phys_from_int(int32_t x, int32_t y, int32_t vx, int32_t vy);

int physics_step_bullet_lorentz(
    PhysBullet_t *b,
    const int16_t *ax, const int16_t *ay, size_t n,
    const LorentzParams_t *p
);

static inline void phys_to_int(const PhysBullet_t *b, int32_t *x, int32_t *y)
{
    *x = FX16_TO_INT(b->x);
    *y = FX16_TO_INT(b->y);
}


#endif
