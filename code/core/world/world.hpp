#ifndef WORLD_INCLUDED_F6D825F0_D062_4B85_A636_7EDE94635488
#define WORLD_INCLUDED_F6D825F0_D062_4B85_A636_7EDE94635488


#include <core/world/world_fwd.hpp>
#include <core/world/detail/world_detail_fwd.hpp>
#include <core/entity/entity_fwd.hpp>
#include <functional>
#include <memory>
#include <stdint.h>


namespace Core {


class World final
{

  World(const World&) = delete;
  World& operator=(const World&) = delete;

public:

  explicit              World(const World_setup &setup);
                        ~World();

  void                  think(const float dt);
  void                  get_overlapping_aabbs(const std::function<void(const Entity_ref ref_a, const Entity_ref ref_b)> &callback);

  Entity_ref            find_entity(const char *name);
  
private:

  friend class Core::Entity;
  friend class Core::Entity_ref;

  std::shared_ptr<const World_detail::World_data>  get_world_data() const;

private:

  struct Impl;
  std::unique_ptr<Impl> m_impl;

};


} // ns


#endif // inc guard