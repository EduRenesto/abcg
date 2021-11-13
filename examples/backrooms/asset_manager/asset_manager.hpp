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

  std::shared_ptr<Asset> get(const std::string& name);

private:
  std::map<std::string, std::shared_ptr<Asset>> m_assets{};
};

#endif
