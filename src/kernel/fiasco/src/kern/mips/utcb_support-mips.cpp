//-------------------------------------------------------------------------
IMPLEMENTATION [mips]:

IMPLEMENT inline
User<Utcb>::Ptr
Utcb_support::current()
{
  Utcb *u;
  asm volatile ("mr %0, %%r2" : "=r" (u));
  return User<Utcb>::Ptr(u);
}

IMPLEMENT inline
void
Utcb_support::current(User<Utcb>::Ptr const &utcb)
{
  asm volatile ("mr %%r2, %0" : : "r" (utcb.get()) : "memory");
}
