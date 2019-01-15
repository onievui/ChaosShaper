#include "Character.h"
#include "ErrorMessage.h"


const int Character::PARTS_MAX = 10;	//�ő啔�ʐ�
const int Character::ITEMS_MAX = 10;	//�ő�A�C�e��������

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_name">���O</param>
Character::Character(const std::string& _name)
	: name(_name)
	, parts{}
	, items{}
	, parameter() {
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_name">���O</param>
/// <param name="_parts">���ʃ��X�g</param>
/// <param name="_items">�A�C�e�����X�g</param>
/// <param name="_parameter">�p�����[�^</param>
Character::Character(const std::string& _name, std::vector<std::unique_ptr<Part>>&& _parts,
	std::vector<std::unique_ptr<Item>>&& _items, const CharaParameter& _parameter) 
	: name(_name)
	, parts(std::move(_parts))
	, items(std::move(_items))
	, parameter(_parameter) {
}

/// <summary>
/// ���O�̎擾
/// </summary>
/// <returns>
/// ���O
/// </returns>
std::string& Character::getName() {
	return name;
}

/// <summary>
/// ���O�̐ݒ�
/// </summary>
/// <param name="_name">���O</param>
void Character::setName(std::string& _name) {
	name = _name;
}

/// <summary>
/// ���ʂ̒ǉ�
/// </summary>
/// <param name="_part">�ǉ����镔��</param>
/// <returns>
/// true : ����
/// false : ���s
/// </returns>
bool Character::addPart(std::unique_ptr<Part>&& _part) {
	if (parts.size() == PARTS_MAX) {
		return false;
	}
	parts.emplace_back(std::move(_part));
	return true;
}

/// <summary>
/// �������ʂ̒ǉ�
/// </summary>
/// <param name="_parts">���ʃ��X�g</param>
/// <returns>
/// true : ����
/// false : ���s
/// </returns>
bool Character::addParts(std::vector<std::unique_ptr<Part>>&& _parts) {
	int pri_size = parts.size();
	int add_size = _parts.size();
	if (pri_size == PARTS_MAX || add_size == 0) {
		return false;
	}
	//�ő啔�ʐ��ɓ��B�����烋�[�v���I������
	for (int i = 0; i < add_size && pri_size + i < PARTS_MAX; ++i) {
		parts.emplace_back(std::move(_parts[i]));
	}
	return true;
}

/// <summary>
/// ���ʂ̎擾
/// </summary>
/// <returns>
/// ����
/// </returns>
std::vector<std::unique_ptr<Part>>& Character::getParts() {
	return parts;
}

/// <summary>
/// �A�C�e���̒ǉ�
/// </summary>
/// <param name="_item">�A�C�e��</param>
/// <returns>
/// true : ����
/// false : ���s
/// </returns>
bool Character::addItem(std::unique_ptr<Item>&& _item) {
	if (items.size() == ITEMS_MAX) {
		return false;
	}
	items.emplace_back(std::move(_item));
	return true;
}

/// <summary>
/// �����A�C�e���̒ǉ�
/// </summary>
/// <param name="_items">�A�C�e�����X�g</param>
/// <returns>
/// true : ����
/// false : ���s
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
/// �A�C�e���̎擾
/// </summary>
/// <returns>
/// �A�C�e��
/// </returns>
std::vector<std::unique_ptr<Item>>& Character::getItems() {
	return items;
}

/// <summary>
/// �X�e�[�^�X�̐ݒ�
/// </summary>
/// <param name="_parameter">�X�e�[�^�X</param>
void Character::setStatus(const CharaParameter& _parameter) {
	parameter = _parameter;
}

/// <summary>
/// ���X�e�[�^�X�̎擾
/// </summary>
/// <returns>
/// ���X�e�[�^�X
/// </returns>
const CharaParameter& Character::getDefaultStatus() {
	return parameter;
}

/// <summary>
/// �X�e�[�^�X�̎擾
/// </summary>
/// <returns>
/// �X�e�[�^�X
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
/// �����i�̑���
/// </summary>
/// <param name="it">�A�C�e�����X�g�̃C�e���[�^</param>
/// <returns>
/// true : ����
/// false : ���s
/// </returns>
bool Character::equipItem(std::vector<std::unique_ptr<Item>>::iterator& it) {
	//�����i�łȂ��Ȃ珈�����Ȃ�
	Equipment* equip = dynamic_cast<Equipment*>(it->get());
	if (!equip) {
		ErrorMessage("�����i�łȂ����̂𑕔����悤�Ƃ��Ă��܂�");
		return false;
	}
	for (const auto& part : parts) {
		//�������Ȃ��΂�
		if (part->isEquipping()) {
			continue;
		}
		//�����\�Ȃ瑕��
		if (part->canEquip(equip)) {
			//�h���N���X�ɕϊ����đ���������
			part->setEquipment(std::make_unique<Equipment>(*equip));
			//���X�g����폜����
			it = items.erase(it);
			return true;
		}
	}
	return false;
}

/// <summary>
/// �����i�̎�������
/// </summary>
void Character::autoEquipping() {
	for (auto it = items.begin(); it != items.end();) {
		//�����i�łȂ��Ȃ��΂�
		Equipment* equip = dynamic_cast<Equipment*>(it->get());
		if (!equip) {
			++it;
			continue;
		}
		//�����Ɏ��s������C�e���[�^��i�߂�
		if (!equipItem(it)) {
			++it;
		}
	}
}

/// <summary>
/// �����i�̉���
/// </summary>
/// <param name="_part_index">���ʃ��X�g�̃C���f�b�N�X</param>
void Character::removeEquipment(const int _part_index) {
	std::unique_ptr<Equipment> equip = parts[_part_index]->removeEquipment();
	addItem(std::move(equip));
}

/// <summary>
/// �_���[�W��^����
/// </summary>
/// <param name="_damage">�_���[�W��</param>
void Character::damage(const int _damage) {
	parameter.hp -= _damage;
	if (parameter.hp < 0) {
		parameter.hp = 0;
	}
}

/// <summary>
/// HP�̍X�V(������)
/// </summary>
void Character::updateHp() {
}


