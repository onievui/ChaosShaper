#include "Character.h"
#include "ErrorMessage.h"


const int Character::PARTS_MAX = 10;	//最大部位数
const int Character::ITEMS_MAX = 10;	//最大アイテム所持数

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_name">名前</param>
Character::Character(const std::string& _name)
	: name(_name)
	, parts{}
	, items{}
	, parameter() {
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_name">名前</param>
/// <param name="_parts">部位リスト</param>
/// <param name="_items">アイテムリスト</param>
/// <param name="_parameter">パラメータ</param>
Character::Character(const std::string& _name, std::vector<std::unique_ptr<Part>>&& _parts,
	std::vector<std::unique_ptr<Item>>&& _items, const CharaParameter& _parameter) 
	: name(_name)
	, parts(std::move(_parts))
	, items(std::move(_items))
	, parameter(_parameter) {
}

/// <summary>
/// 名前の取得
/// </summary>
/// <returns>
/// 名前
/// </returns>
std::string& Character::getName() {
	return name;
}

/// <summary>
/// 名前の設定
/// </summary>
/// <param name="_name">名前</param>
void Character::setName(std::string& _name) {
	name = _name;
}

/// <summary>
/// 部位の追加
/// </summary>
/// <param name="_part">追加する部位</param>
/// <returns>
/// true : 成功
/// false : 失敗
/// </returns>
bool Character::addPart(std::unique_ptr<Part>&& _part) {
	if (parts.size() == PARTS_MAX) {
		return false;
	}
	parts.emplace_back(std::move(_part));
	return true;
}

/// <summary>
/// 複数部位の追加
/// </summary>
/// <param name="_parts">部位リスト</param>
/// <returns>
/// true : 成功
/// false : 失敗
/// </returns>
bool Character::addParts(std::vector<std::unique_ptr<Part>>&& _parts) {
	int pri_size = parts.size();
	int add_size = _parts.size();
	if (pri_size == PARTS_MAX || add_size == 0) {
		return false;
	}
	//最大部位数に到達したらループを終了する
	for (int i = 0; i < add_size && pri_size + i < PARTS_MAX; ++i) {
		parts.emplace_back(std::move(_parts[i]));
	}
	return true;
}

/// <summary>
/// 部位の取得
/// </summary>
/// <returns>
/// 部位
/// </returns>
std::vector<std::unique_ptr<Part>>& Character::getParts() {
	return parts;
}

/// <summary>
/// アイテムの追加
/// </summary>
/// <param name="_item">アイテム</param>
/// <returns>
/// true : 成功
/// false : 失敗
/// </returns>
bool Character::addItem(std::unique_ptr<Item>&& _item) {
	if (items.size() == ITEMS_MAX) {
		return false;
	}
	items.emplace_back(std::move(_item));
	return true;
}

/// <summary>
/// 複数アイテムの追加
/// </summary>
/// <param name="_items">アイテムリスト</param>
/// <returns>
/// true : 成功
/// false : 失敗
/// </returns>
bool Character::addItems(std::vector<std::unique_ptr<Item>>&& _items) {
	int pri_size = items.size();
	int add_size = _items.size();
	if (pri_size == ITEMS_MAX || add_size == 0) {
		return false;
	}

	for (int i = 0; i < add_size && pri_size + i < ITEMS_MAX; ++i) {
		items.emplace_back(std::move(_items[i]));
	}
	return true;
}

/// <summary>
/// アイテムの取得
/// </summary>
/// <returns>
/// アイテム
/// </returns>
std::vector<std::unique_ptr<Item>>& Character::getItems() {
	return items;
}

/// <summary>
/// ステータスの設定
/// </summary>
/// <param name="_parameter">ステータス</param>
void Character::setStatus(const CharaParameter& _parameter) {
	parameter = _parameter;
}

/// <summary>
/// 元ステータスの取得
/// </summary>
/// <returns>
/// 元ステータス
/// </returns>
const CharaParameter& Character::getDefaultStatus() {
	return parameter;
}

/// <summary>
/// ステータスの取得
/// </summary>
/// <returns>
/// ステータス
/// </returns>
CharaParameter Character::getStatus() {
	CharaParameter final_parameter = parameter;
	int total_attack_level = 0;
	int total_defence_level = 0;
	for (const auto &part : parts) {
		if (part->isEquipping()) {
			final_parameter.addParameter(part->getEquipment()->getParameter());
		}
		if (part->getPartType().equal(PartType::Arm)) {
			total_attack_level += part->getLevel();
		}
		else {
			total_defence_level += part->getLevel();
		}
	}
	final_parameter.attack = final_parameter.attack*(total_attack_level + 10) / 10;
	final_parameter.defence = final_parameter.defence*(total_defence_level + 10) / 10;
	return final_parameter;
}

/// <summary>
/// 装備品の装備
/// </summary>
/// <param name="it">アイテムリストのイテレータ</param>
/// <returns>
/// true : 成功
/// false : 失敗
/// </returns>
bool Character::equipItem(std::vector<std::unique_ptr<Item>>::iterator& it) {
	//装備品でないなら処理しない
	Equipment* equip = dynamic_cast<Equipment*>(it->get());
	if (!equip) {
		ErrorMessage("装備品でないものを装備しようとしています");
		return false;
	}
	for (const auto& part : parts) {
		//装備中なら飛ばす
		if (part->isEquipping()) {
			continue;
		}
		//装備可能なら装備
		if (part->canEquip(equip)) {
			//派生クラスに変換して装備させる
			part->setEquipment(std::make_unique<Equipment>(*equip));
			//リストから削除する
			it = items.erase(it);
			return true;
		}
	}
	return false;
}

/// <summary>
/// 装備品の自動装備
/// </summary>
void Character::autoEquipping() {
	for (auto it = items.begin(); it != items.end();) {
		//装備品でないなら飛ばす
		Equipment* equip = dynamic_cast<Equipment*>(it->get());
		if (!equip) {
			++it;
			continue;
		}
		//装備に失敗したらイテレータを進める
		if (!equipItem(it)) {
			++it;
		}
	}
}

/// <summary>
/// 装備品の解除
/// </summary>
/// <param name="_part_index">部位リストのインデックス</param>
void Character::removeEquipment(const int _part_index) {
	std::unique_ptr<Equipment> equip = parts[_part_index]->removeEquipment();
	addItem(std::move(equip));
}

/// <summary>
/// ダメージを与える
/// </summary>
/// <param name="_damage">ダメージ量</param>
void Character::damage(const int _damage) {
	parameter.hp -= _damage;
	if (parameter.hp < 0) {
		parameter.hp = 0;
	}
}

/// <summary>
/// HPの更新(実装無)
/// </summary>
void Character::updateHp() {
}


