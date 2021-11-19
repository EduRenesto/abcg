project(sponza)

set(sponza_sources
  main.cpp
  gl_window.cpp
  input.cpp
  asset_manager/asset.cpp
  asset_manager/asset_manager.cpp
  asset_manager/mesh_asset.cpp
  asset_manager/shader_asset.cpp
  rendering/mesh.cpp
  rendering/transform.cpp
  rendering/camera.cpp
  level/level.cpp
  systems/mesh_renderer.cpp
  systems/camera_system.cpp
  )

add_executable(sponza ${sponza_sources})

enable_abcg(sponza)
