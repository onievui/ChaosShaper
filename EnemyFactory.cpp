#include "EnemyFactory.h"
#include "ItemFactory.h"
#include "ErrorMessage.h"
#include "RandMt.h"
#include <algorithm>



/// <summary>
/// �G��������
/// </summary>
/// <param name="_floor">�K�w</param>
/// <returns>
/// �G
/// </returns>
std::unique_ptr<Enemy> EnemyFactory::createEnemy(const int _floor) {
	//�����N�̐���
	int rank = RandMt::GetRand(_floor / 10 + 1);

	//���O�̐���
	EnemyID enemy_id = (EnemyID)RandMt::GetRand((std::min)(_floor / 6 + 2, (int)EnemyID::Num));
	auto enemy = std::make_unique<Enemy>(generateName(enemy_id, rank));

	//�p�����[�^�̐���
	enemy->setStatus(generateParameter(enemy_id, rank, _floor));

	//���ʂ̐���
	enemy->addParts(generateParts(_floor));

	//�����̐���
	enemy->addItems(ItemFactory::createItems(_floor));

	//��������
	enemy->autoEquipping();

	return enemy;
}

/// <summary>
/// ���O�̐���
/// </summary>
/// <param name="_enemy_id">�GID</param>
/// <param name="_rank">�����N</param>
/// <returns>
/// ���O
/// </returns>
std::string EnemyFactory::generateName(const EnemyID _enemy_id, const int _rank) {
	std::string name;
	
	switch (_enemy_id) {
	case EnemyID::Slime:
		name.append("�X���C��");
		break;
	case EnemyID::Goblin:
		name.append("�S�u����");
		break;
	case EnemyID::Ghost:
		name.append("�S�[�X�g");
		break;
	case EnemyID::Man:
		name.append("��������");
		break;
	case EnemyID::Dragon:
		name.append("�h���S��");
		break;
	default:
		ErrorMessage("���O�̐����ŕs���Ȓl���n����܂�������܂���");
		break;
	}

	return name;
}

/// <summary>
/// �p�����[�^�̐���
/// </summary>
/// <param name="_enemy_id">�GID</param>
/// <param name="_rank">�����N</param>
/// <param name="_floor">�K�w</param>
/// <returns>
/// �p�����[�^
/// </returns>
CharaParameter EnemyFactory::generateParameter(const EnemyID _enemy_id, const int _rank, const int _floor) {

	CharaParameter parameter;

	switch (_enemy_id) {
	case EnemyID::Slime:
		parameter = CharaParameter(_floor, 10, 2, 2, 2, 0);
		break;
	case EnemyID::Goblin:
		parameter = CharaParameter(_floor, 15, 3, 3, 3, 3);
		break;
	case EnemyID::Ghost:
		parameter = CharaParameter(_floor, 13, 3, 2, 5, 2);
		break;
	case EnemyID::Man:
		parameter = CharaParameter(_floor, 20, 4, 4, 4, 3);
		break;
	case EnemyID::Dragon:
		parameter = CharaParameter(_floor, 30, 6, 6, 6, 5);
		break;
	default:
		ErrorMessage("�p�����[�^�̐����ŕs���Ȓl���n����܂�������܂���");
		break;
	}

	parameter.levelUp(_floor - 1);

	return parameter;
}

/// <summary>
/// ���ʂ̐���
/// </summary>
/// <param name="_floor">�K�w</param>
/// <returns>
/// ����
/// </returns>
std::vector<std::unique_ptr<Part>> EnemyFactory::generateParts(const int _floor) {
	std::vector<std::unique_ptr<Part>> parts;
	int get_parts_num = (std::min)(RandMt::GetRand(2) + _floor / 6, Character::PARTS_MAX);
	for (int i = 0; i < get_parts_num; ++i) {
		PartType part_type = (PartType)RandMt::GetRand(PartType::Num.getData());
		parts.emplace_back(std::make_unique<Part>(part_type, _floor));
	}

	return parts;
}
