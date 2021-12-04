#ifndef __SPONZA_MESH_ASSET_HPP
#define __SPONZA_MESH_ASSET_HPP

#include <memory>
#include <string>
#include <optional>
#include <utility>

#include "asset.hpp"
#include "../rendering/mesh.hpp"

class MeshAsset : public Asset {
public:
  explicit MeshAsset(std::string path) : m_path(std::move(path)) {}

  const std::vector<Mesh>& get();

  static std::shared_ptr<Asset> build(std::string path);

private:
  std::string m_path;

  std::optional<std::vector<Mesh>> m_meshes{std::nullopt};
};

#endif
