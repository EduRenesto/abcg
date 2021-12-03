#include "mesh_asset.hpp"

#include <filesystem>

#include <tiny_obj_loader.h>
#include <fmt/format.h>

#include "abcg_exception.hpp"

const Mesh& MeshAsset::get() {
  if (this->m_mesh.has_value()) {
    return this->m_mesh.value();
  }

  fmt::print("Loading model asset from {}...\n", this->m_path);

  const auto base_path{std::filesystem::path{this->m_path}.parent_path().string() + "/"};
  tinyobj::ObjReaderConfig reader_cfg;
  reader_cfg.mtl_search_path = base_path;

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(this->m_path, reader_cfg)) {
    auto err{fmt::format("Failed to load {}: {}", this->m_path, reader.Error())};
    throw abcg::Exception{abcg::Exception::Runtime(err)};
  }

  const auto& attribs{reader.GetAttrib()};
  const auto& shapes{reader.GetShapes()};
  const auto& src_materials{reader.GetMaterials()};

  std::vector<glm::vec3> positions{};
  std::vector<glm::vec3> normals{};
  std::vector<glm::vec2> tex_coords{};

  std::vector<Material> materials{};
  std::vector<int> material_indices{};

  materials.reserve(src_materials.size());
  for (const auto& material : src_materials) {
    materials.emplace_back(material.diffuse_texname);
  }

  fmt::print("total materials: {}\n", materials.size());

  // No indexing here, just raw vertices.

  for (const auto& shape : shapes) {
    auto face_idx = 0;
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

      const auto tex_coord{glm::vec2{
	  attribs.texcoords.at(2 * face.texcoord_index),
	  attribs.texcoords.at(2 * face.texcoord_index + 1),
      }};

      //fmt::print("shape.mesh.material_ids.len = {}\n", shape.mesh.material_ids.size());
      //fmt::print("shape.mesh.indices.len = {}\n", shape.mesh.indices.size());
      //fmt::print("face_idx/3 = {}\n", face_idx/3);
      const auto material_index{shape.mesh.material_ids.at(face_idx/3)};

      positions.push_back(vertex);
      normals.push_back(normal);
      tex_coords.push_back(tex_coord);
      material_indices.push_back(material_index);

      face_idx++;
    }
  }

  auto mesh = Mesh{
    std::move(positions),
    std::move(normals),
    std::move(tex_coords),
    std::move(material_indices),
    std::move(materials),
  };

  this->m_mesh = std::optional{std::move(mesh)};

  return this->m_mesh.value();
}

std::shared_ptr<Asset> MeshAsset::build(std::string path) {
  auto specialized = std::make_shared<MeshAsset>(MeshAsset{std::move(path)});

  return std::static_pointer_cast<Asset>(specialized);
}
