project(backrooms)

set(backrooms_sources
  main.cpp
  asset_manager/asset.cpp
  asset_manager/asset_manager.cpp
  asset_manager/mesh_asset.cpp
  rendering/mesh.cpp
  systems/mesh_renderer.cpp)

add_executable(backrooms ${backrooms_sources})

enable_abcg(backrooms)
