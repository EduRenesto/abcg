#ifndef __BACKROOMS_MESH_ASSET_HPP
#define __BACKROOMS_MESH_ASSET_HPP

#include <memory>
#include <string>
#include <optional>
#include <utility>

#include "asset.hpp"
#include "../rendering/mesh.hpp"

class MeshAsset : public Asset {
public:
  explicit MeshAsset(std::string path) : m_path(std::move(path)) {}

  const Mesh& get();

  static std::shared_ptr<Asset> build(std::string path);

private:
  std::string m_path;

  std::optional<Mesh> m_mesh{std::nullopt};
};

#endif
