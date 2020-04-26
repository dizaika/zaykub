#ifndef IGAMEABLE_H
#define IGAMEABLE_H

class IGameable
{
public:
  virtual void Run(int FirstPlayer, uint32_t FirstColor, uint32_t SecondColor) = 0;
};
  
#endif
