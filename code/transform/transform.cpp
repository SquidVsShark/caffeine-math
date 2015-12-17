#include "transform.hpp"


namespace Transform {


void
transforms_to_wvp_mats(const math::transform input_transforms[],
                       const std::size_t number_of_input_transforms,
                       const math::mat4 view_proj_mat,
                       void  *output_mats,
                       const std::size_t number_of_output_mats,
                       const std::size_t byte_stride)
                        {
                          const uint32_t number_to_process = static_cast<uint32_t>(math::min(number_of_input_transforms, number_of_output_mats));
                        
                          for(std::size_t i = 0; i < number_to_process; ++i)
                          {
                            // Calculate wvp matrix.
                            const math::mat4 world_mat = math::transform_get_world_matrix(input_transforms[i]);
                            const math::mat4 wvp_mat = math::mat4_multiply(world_mat, view_proj_mat);
                            
                            // Starting point taking into account stride.
                            uint8_t *data = &reinterpret_cast<uint8_t*>(output_mats)[byte_stride * i];
                            
                            // Insert point after stride taken into account.
                            float *out_data = reinterpret_cast<float*>(data);
                            
                            // Insert result into output.
                            math::mat4_to_array(wvp_mat, out_data);
                          }
                        }


void
transforms_to_world_mats(const math::transform input_transforms[],
                         const std::size_t number_of_input_transforms,
                         void  *output_mats,
                         const std::size_t number_of_output_mats,
                         const std::size_t byte_stride)
                         {
                           const uint32_t number_to_process = static_cast<uint32_t>(math::min(number_of_input_transforms, number_of_output_mats));
                         
                           for(std::size_t i = 0; i < number_to_process; ++i)
                           {
                             // Calculate wvp matrix.
                             const math::mat4 world_mat = math::transform_get_world_matrix(input_transforms[i]);
                             
                             // Starting point taking into account stride.
                             uint8_t *data = &reinterpret_cast<uint8_t*>(output_mats)[byte_stride * i];
                             
                             // Insert point after stride taken into account.
                             float *out_data = reinterpret_cast<float*>(data);
                             
                             // Insert result into output.
                             math::mat4_to_array(world_mat, out_data);
                           }
                         }


} // ns