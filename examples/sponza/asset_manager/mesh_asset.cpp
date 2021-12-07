#include "mesh_asset.hpp"

#include <filesystem>

#include <tiny_obj_loader.h>
#include <fmt/format.h>

#include "abcg_exception.hpp"

const std::vector<Mesh>& MeshAsset::get() {
  if (this->m_meshes.has_value()) {
    return this->m_meshes.value();
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

  std::vector<Material> materials{};

  materials.reserve(src_materials.size());
  for (const auto& material : src_materials) {
    /*
    fmt::print(
	       "name = {}, diffuse_texname = {}, normal_texname = {}, bump_texname = {}\n",
	       material.name,
	       material.diffuse_texname,
	       material.normal_texname,
	       material.bump_texname);
    */
    if (material.diffuse_texname.empty()) {
      materials.push_back(Material{"textures/default", material.shininess});
    } else {
      materials.push_back(Material{material.diffuse_texname, material.shininess});
    }
  }

  //fmt::print("total materials: {}\n", materials.size());

  std::vector<Mesh> meshes{};

  for (const auto& shape : shapes) {
    // No indexing here, just raw vertices.
    std::vector<glm::vec3> positions{};
    std::vector<glm::vec3> normals{};
    std::vector<glm::vec2> tex_coords{};

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
      //const auto material_index{shape.mesh.material_ids.at(face_idx/3)};

      positions.push_back(vertex);
      normals.push_back(normal);
      tex_coords.push_back(tex_coord);
      //material_indices.push_back(material_index);

      face_idx++;
    }
    
    auto mesh = Mesh{
      shape.name,
      std::move(positions),
      std::move(normals),
      std::move(tex_coords),
      Material{materials.at(shape.mesh.material_ids.at(0))},
      //std::move(material_indices),
      //std::move(materials),
    };

    meshes.push_back(mesh);
  }

  fmt::print("Loaded {} meshes from {}\n", meshes.size(), this->m_path);

  //this->m_mesh = std::optional{std::move(mesh)};
  this->m_meshes = std::optional{std::move(meshes)};

  return this->m_meshes.value();
}

std::shared_ptr<Asset> MeshAsset::build(std::string path) {
  auto specialized = std::make_shared<MeshAsset>(MeshAsset{std::move(path)});

  return std::static_pointer_cast<Asset>(specialized);
}
