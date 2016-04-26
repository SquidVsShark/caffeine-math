 #include "world.hpp"
#include <core/world/world_setup.hpp>

#include <core/memory/memory.hpp>

#include <graphics_api/initialize.hpp>
#include <graphics_api/clear.hpp>

#include <core/entity/entity.hpp>
#include <core/entity/entity_ref.hpp>

#include <renderer/renderer.hpp>
#include <renderer/simple_renderer/simple_renderer.hpp>
#include <renderer/debug_line_renderer/debug_line_renderer.hpp>
#include <renderer/gui_renderer/gui_renderer.hpp>

#include <core/world/detail/world_detail.hpp>

#include <utilities/logging.hpp>

#include <systems/physics_engine/physics_engine.hpp>

#include <data/world_data/sweep_and_prune.hpp>


namespace Core {


struct World::Impl
{
  std::shared_ptr<World_detail::World_data> world_data = std::make_shared<World_detail::World_data>();
};


World::World(const World_setup &setup)
: m_impl(new World::Impl)
{
  const size_t chunk_128_mb = 134217728;
  Core::Memory::initialize(chunk_128_mb);

  LOG_TODO("Remove static data stores")
  static World_data::Entity_pool world_entities;
  World_data::entity_pool_init(&world_entities);
  
  static World_data::Entity_graph_changes_pool graph_changes;
  World_data::entity_graph_change_pool_init(&graph_changes);
  
  static World_data::Camera_pool camera_pool;
  World_data::camera_pool_init(&camera_pool);
  
  static World_data::Gui_view_pool gui_view_pool;
  World_data::gui_view_pool_init(&gui_view_pool);
  
  static World_data::Application_window app_window;
  World_data::application_window_init(&app_window);
  
  m_impl->world_data->data.entity_pool            = &world_entities;
  m_impl->world_data->data.entity_graph_changes   = &graph_changes;
  m_impl->world_data->data.camera_pool            = &camera_pool;
  m_impl->world_data->data.gui_pool               = &gui_view_pool;
  
  LOG_TODO("We can store the data directly and get rid of ::World_data::World")
  World_data::set_world_data(&m_impl->world_data->data);
}


World::~World()
{
}


void
World::think(const float dt)
{
  // Push in new phy entities.
  World_data::world_update_scene_graph_changes(&m_impl->world_data->data, m_impl->world_data->data.entity_graph_changes);
  
  // Reset the entity pool for new changes.
  World_data::entity_graph_change_pool_init(m_impl->world_data->data.entity_graph_changes);
}


void
//World::get_overlapping_aabbs(const std::function<void(const Entity_ref ref_a, const Entity_ref ref_b)> &callback)
World::get_overlapping_aabbs(const std::function<void(const Physics_engine::Collision_pair pairs[],
                                                      const uint32_t number_of_pairs)> &callback)
{
  // Check we have a callback.
  if(!callback) { return; }

  // TODO need this on a memory pool, get it out of the stack.
//  constexpr uint32_t max_collisions = 1 << 13;
//  Physics_engine::Collision_pair out_collisions[max_collisions];
//  uint32_t out_number_of_collisions(0);
//  {
    const World_data::Entity_pool *entity_data = m_impl->world_data->data.entity_pool;
//
//    // Get the collisions.
//    Physics_engine::get_collisions(entity_data->entity_id,
//                                   entity_data->transform,
//                                   entity_data->aabb,
//                                   entity_data->size,
//                                   out_collisions,
//                                   max_collisions,
//                                   &out_number_of_collisions);
  
  // Create aabbs with tranforms
//  math::aabb transformed_aabbs[2048];
  std::vector<math::aabb> transformed_aabbs;
  
  for(uint32_t i = 0; i < entity_data->size; ++i)
  {
    math::aabb copy(entity_data->aabb[i]);
    math::aabb_scale(copy, entity_data->transform[i].scale);
    copy.origin = entity_data->transform[i].position;
    //transformed_aabbs[i] = copy;
    transformed_aabbs.push_back(copy);
  }
  
  World_data::Sweep_and_prune sweep;
  World_data::sweep_and_prune_create(&sweep,
                                     entity_data->entity_id,
                                     transformed_aabbs.data(),
                                     entity_data->size,
                                     math::aabb_init(math::vec3_init(50, 50, 50), math::vec3_init(-50, -50, -50), math::vec3_zero()));
  
  for(uint32_t i = 0; i < 8 * 8 * 8; ++i)
  {
    if(sweep.bucket[i].size)
    {
      const std::string size = "bucket " + std::to_string(i) + " size:" + std::to_string(sweep.bucket[i].size);
      
      LOG_INFO(size.c_str())
    }
  }
//  }

//  callback(out_collisions, out_number_of_collisions);

  // Log a warning if we have max out the collision buffer.
//  {
//    static int log_max_warning_once = 0;
//    if(out_number_of_collisions >= max_collisions && !log_max_warning_once)
//    {
//      log_max_warning_once = 1;
//      LOG_WARNING("Collisions have maxed out.")
//    }
//  }
}


Entity_ref
World::find_entity_by_name(const char *name)
{
  return Entity_ref();
}


Entity_ref
World::find_entity_by_id(const Core::Entity_id id)
{
  return Entity_ref(id, &m_impl->world_data->data);
}


std::shared_ptr<const World_detail::World_data>
World::get_world_data() const
{
  assert(m_impl);
  return m_impl->world_data;
}



} // ns