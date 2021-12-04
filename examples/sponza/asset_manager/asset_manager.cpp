#include "asset_manager.hpp"
#include "abcg_exception.hpp"

#include <fmt/format.h>
#include <stdlib.h>

void AssetManager::add(std::string name, std::shared_ptr<Asset> asset) {
  this->m_assets[std::move(name)] = std::move(asset);
}

std::shared_ptr<Asset> AssetManager::get_raw(const std::string& name) {
  if (!this->m_assets.contains(name)) {
    auto err = fmt::format("[AssetManager] No such asset {}", name);
    abort();
    throw abcg::Exception{abcg::Exception::Runtime(err)};
  }

  return this->m_assets[name];
}
