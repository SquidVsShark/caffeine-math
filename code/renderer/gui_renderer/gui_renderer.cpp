#include "gui_renderer.hpp"
#include <graphics_api/texture_filtering.hpp>
#include <graphics_api/ogl/ogl_texture_filtering.hpp>
#include <graphics_api/ogl/ogl_common.hpp>
#include <graphics_api/ogl/ogl_shader.hpp>
#include <graphics_api/ogl/ogl_shader_uniform.hpp>
#include <graphics_api/ogl/ogl_texture.hpp>
#include <graphics_api/ogl/ogl_vertex_format.hpp>
#include <graphics_api/ogl/ogl_vertex_buffer.hpp>
#include <graphics_api/ogl/ogl_index_buffer.hpp>
#include <graphics_api/utils/shader_utils.hpp>
#include <graphics_api/ogl/ogl_blend.hpp>
#include <utilities/directory.hpp>
#include <string>
#include <assert.h>
#include <iostream>


namespace
{
  Ogl::Shader                       shader_gui;
  Ogl::Vertex_format                gui_vertex_format;
  Ogl::Vertex_buffer                quad_vbo;
  Ogl::Index_buffer                 quad_ibo;
  Ogl::Uniform                      uni_wvp_mat;
  Ogl::Uniform                      uni_quad_size;
  Ogl::Uniform                      uni_scale;
  Ogl::Uniform                      uni_quad_color;
  Ogl::Uniform                      uni_diffuse_map;
  Graphics_api::Texture_filtering   texture_filtering;
}


namespace Gui_renderer {


void
initialize()
{
  Ogl::error_clear();

  // Load shader
  {
    const std::string asset_path  = util::get_resource_path() + "assets/";
    const std::string gui_shader  = asset_path + "shaders/gui.ogl";
    
    const auto gui_code = Graphics_api::Util::shader_code_from_tagged_file(gui_shader.c_str());
    
    Ogl::shader_create(&shader_gui, gui_code.vs_code.c_str(), gui_code.gs_code.c_str(), gui_code.ps_code.c_str());
    
    assert(Ogl::shader_is_valid(shader_gui));
  }
  
  // Get the shader's uniforms
  if(Ogl::shader_is_valid(shader_gui))
  {
    Ogl::Shader_uniforms gui_uniforms;
    Ogl::shader_uniforms_retrive(&gui_uniforms, &shader_gui);
    
    Ogl::shader_uniforms_get_uniform_index(&uni_wvp_mat,     &gui_uniforms, "uni_wvp_mat");
    Ogl::shader_uniforms_get_uniform_index(&uni_quad_size,   &gui_uniforms, "uni_quad_size");
    Ogl::shader_uniforms_get_uniform_index(&uni_quad_color,  &gui_uniforms, "uni_color");
    Ogl::shader_uniforms_get_uniform_index(&uni_diffuse_map, &gui_uniforms, "uni_diffuse_map");
    Ogl::shader_uniforms_get_uniform_index(&uni_scale,       &gui_uniforms, "uni_scale");
  }
  
  // Vertex attr
  {
    constexpr uint32_t number_of_attrs = 2;
    const Ogl::Attribute_desc vert_desc[number_of_attrs]
    {
      Ogl::Attribute_desc{"in_vs_position",       Ogl::Attr_type::FLOAT2},
      Ogl::Attribute_desc{"in_vs_texture_coord",  Ogl::Attr_type::FLOAT2},
    };
    
    Ogl::vertex_format_load(&gui_vertex_format, vert_desc, number_of_attrs);
    assert(Ogl::vertex_format_is_valid(&gui_vertex_format));
  }
  
  // Build VBO and IBO
  {
    constexpr uint32_t number_of_entries = 16;
    const float quad_data[number_of_entries]
    {
      -1.f, -1.f, 0.f, 0.f,
      +1.f, -1.f, 1.f, 0.f,
      +1.f, +1.f, 1.f, 1.f,
      -1.f, +1.f, 0.f, 1.f,
    };
    
    Ogl::vertex_buffer_load(&quad_vbo, quad_data, sizeof(quad_data), number_of_entries, false);
    assert(Ogl::vertex_buffer_is_valid(quad_vbo));
    
    constexpr uint32_t number_of_indices = 6;
    const uint32_t index[number_of_indices]
    {
      0,1,2,
      2,3,0,
    };
    
    Ogl::index_buffer_load(&quad_ibo, index, number_of_indices);
    assert(Ogl::index_buffer_is_valid(quad_ibo));
  }
  
  // Default texture filtering
  {
    texture_filtering.wrap_mode_s = Graphics_api::Wrap_mode::clamp;
    texture_filtering.wrap_mode_t = Graphics_api::Wrap_mode::clamp;
    texture_filtering.filtering   = Graphics_api::Filtering_mode::bilinear;
  }
  
  Ogl::error_check("Setting up simple renderers", &std::cout);
}


void
de_initialize()
{
}


void
render_gui_nodes(const Node nodes[],
                 const uint32_t number_of_nodes,
                 const uint32_t view_port_width,
                 const uint32_t view_port_height)
{
  Ogl::error_clear();
  Ogl::default_state();
  
  Ogl::blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  Ogl::shader_bind(&shader_gui);
  
  for(uint32_t n = 0; n < number_of_nodes; ++n)
  {
    const Node *curr_node = &nodes[n];
    assert(curr_node);
    
    float scale[2] = {0.01f, 0.01f};
    Ogl::shader_uniforms_apply(uni_scale, (void*)scale);
    Ogl::shader_uniforms_apply(uni_quad_color, (void*)curr_node->color);
    
    Ogl::filtering_apply(texture_filtering);
    Ogl::vertex_buffer_bind(quad_vbo, &gui_vertex_format, &shader_gui);
    Ogl::index_buffer_draw(GL_TRIANGLES, quad_ibo);
  }
  
  Ogl::error_check("Drawing the gui", &std::cout);
}


} // ns