#ifndef __BACKROOMS_ASSET_MANAGER_HPP
#define __BACKROOMS_ASSET_MANAGER_HPP

#include <memory>
#include <string>
#include <map>

#include "asset.hpp"

class AssetManager {
public:
  AssetManager() = default;

  void add(std::string name, std::shared_ptr<Asset> asset);

  template<class T>
  std::shared_ptr<T> get(const std::string& name) {
    auto ptr = this->get_raw(name);
    return std::static_pointer_cast<T>(ptr);
  }

private:
  std::map<std::string, std::shared_ptr<Asset>> m_assets{};

  std::shared_ptr<Asset> get_raw(const std::string& name);
};

#endif
