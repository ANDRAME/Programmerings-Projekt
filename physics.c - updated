#include "physics.h"
#include <limits.h>

/* ---------- Fixed-point helpers ---------- */
static inline fx16_t fx_mul(fx16_t a, fx16_t b)
{
    return (fx16_t)(((int64_t)a * b) >> 16);
}

static inline fx16_t fx_div(fx16_t a, fx16_t b)
{
    if (!b) return (a > 0) ? INT32_MAX : INT32_MIN;
    return (fx16_t)(((int64_t)a << 16) / b);
}

static inline fx16_t fx_clamp(fx16_t v, fx16_t lo, fx16_t hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static inline void clamp_v(PhysBullet_t *b, fx16_t vmax)
{
    if (vmax <= 0) return;
    b->vx = fx_clamp(b->vx, -vmax, vmax);
    b->vy = fx_clamp(b->vy, -vmax, vmax);
}

/* ---------- Defaults ---------- */
LorentzParams_t lorentz_defaults(void)
{
    LorentzParams_t p;
    p.k      = FX16_FROM_INT(1);
    p.B0     = FX16_FROM_INT(350);   // gentle curve
    p.Bmax   = FX16_FROM_INT(1);
    p.vmax   = FX16_FROM_INT(4);

    p.soft2  = 4;      // ~6px
    p.range2 = 10*10;   // only within 25px
    p.radius = 6;       // asteroid radius
    p.edge   = 2;       // only near the side

    return p;
}

PhysBullet_t phys_from_int(int32_t x, int32_t y, int32_t vx, int32_t vy)
{
    PhysBullet_t b;
    b.x  = FX16_FROM_INT(x);
    b.y  = FX16_FROM_INT(y);
    b.vx = FX16_FROM_INT(vx);
    b.vy = FX16_FROM_INT(vy);
    return b;
}

/* ---------- Main physics ---------- */
int  physics_step_bullet_lorentz(
    PhysBullet_t *b,
    const int16_t *ax, const int16_t *ay, size_t n,
    const LorentzParams_t *p
){
    int32_t bx = FX16_TO_INT(b->x);
    int32_t by = FX16_TO_INT(b->y);

    fx16_t bz_sum = 0;

    for (size_t i = 0; i < n; i++) {
        int32_t dx = bx - ax[i];
        int32_t dy = by - ay[i];
        int32_t r2 = dx*dx + dy*dy;

        /* ---- Activation gate ---- */
        if (r2 > p->range2) continue;

        int32_t rin  = p->radius - p->edge;
        int32_t rout = p->radius + p->edge;

        if (r2 < rin*rin || r2 > rout*rout)
            continue;

        fx16_t bz = fx_div(p->B0, FX16_FROM_INT(r2 + p->soft2));
        bz = fx_clamp(bz, -p->Bmax, p->Bmax);
        if (dx > 0) bz = -bz;
        bz_sum += bz;
    }

    bz_sum = fx_clamp(bz_sum, -p->Bmax, p->Bmax);

    /* Lorentz acceleration */
    fx16_t axf = fx_mul(p->k, fx_mul(b->vy, bz_sum));
    fx16_t ayf = fx_mul(p->k, fx_mul(-b->vx, bz_sum));

    b->vx += axf;
    b->vy += ayf;

    clamp_v(b, p->vmax);

    b->x += b->vx;
    b->y += b->vy;




    return 1;
}
