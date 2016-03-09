#include "physics_engine.hpp"


namespace Physics_engine {

void
get_collisions(
  const Core::Entity_id ids[],
  const math::transform transforms[],
  const math::aabb aabbs[],
  const uint32_t number_of_entities_to_test,
  Collision_pair out_ids[],
  const uint32_t size_of_out_buffer,
  uint32_t *number_of_collisions
)
{
  for(uint32_t i = 0; i < number_of_entities_to_test; ++i)
  {
    math::aabb aabb_a = aabbs[i];
    aabb_a.origin = transforms[i].position;
  
    for(uint32_t j = (i + 1); j < (number_of_entities_to_test - 1); ++j)
    {
      if(i != j)
      {    
        math::aabb aabb_b = aabbs[j];
        aabb_b.origin = transforms[j].position;
        
        if(math::aabb_intersection_test(aabb_a, aabb_b))
        {
        
        }
      }
    }
  }
}


} // ns