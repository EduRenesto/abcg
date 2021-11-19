#include "mesh_asset.hpp"

#include <tiny_obj_loader.h>
#include <fmt/format.h>

#include "abcg_exception.hpp"

const Mesh& MeshAsset::get() {
  if (this->m_mesh.has_value()) {
    return this->m_mesh.value();
  }

  fmt::print("Loading model asset from {}...\n", this->m_path);

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(this->m_path)) {
    auto err{fmt::format("Failed to load {}: {}", this->m_path, reader.Error())};
    throw abcg::Exception{abcg::Exception::Runtime(err)};
  }

  const auto& attribs{reader.GetAttrib()};
  const auto& shapes{reader.GetShapes()};

  std::vector<glm::vec3> positions{};
  std::vector<glm::vec3> normals{};

  // No indexing here, just raw vertices.

  for (const auto& shape : shapes) {
    for (const auto& face : shape.mesh.indices) {
      const auto vertex{glm::vec3{
	  attribs.vertices.at(3 * face.vertex_index),
	  attribs.vertices.at(3 * face.vertex_index + 1),
	  attribs.vertices.at(3 * face.vertex_index + 2),
      }};

      const auto normal{glm::vec3{
	  attribs.normals.at(3 * face.normal_index),
	  attribs.normals.at(3 * face.normal_index + 1),
	  attribs.normals.at(3 * face.normal_index + 2),
      }};

      positions.push_back(vertex);
      normals.push_back(normal);
    }
  }

  auto mesh = Mesh{std::move(positions), std::move(normals)};

  this->m_mesh = std::optional{std::move(mesh)};

  return this->m_mesh.value();
}

std::shared_ptr<Asset> MeshAsset::build(std::string path) {
  auto specialized = std::make_shared<MeshAsset>(MeshAsset{std::move(path)});

  return std::static_pointer_cast<Asset>(specialized);
}
