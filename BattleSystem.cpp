#include "BattleSystem.h"
#include "ErrorMessage.h"
#include "RandMt.h"
#include <vector>


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_player">�v���C���[�ւ̃|�C���^</param>
/// <param name="_enemy">�G�ւ̃|�C���^</param>
BattleSystem::BattleSystem(Player* _player, Enemy* _enemy)
	: player(_player)
	, enemy(_enemy) {
}

/// <summary>
/// �퓬����
/// </summary>
void BattleSystem::battle() {
	//CharaParameter player_status = player->getStatus();
	//CharaParameter enemy_status = enemy->getStatus();
	//CharaParameter* first_chara;
	//CharaParameter* next_chara;
	Character* first_chara;
	Character* next_chara;
	std::vector<AttackParameter> first_attack_parameter;
	std::vector<AttackParameter> next_attack_parameter;

	//��U�����߂�
	if (decideFirst(player->getStatus(), enemy->getStatus())) {
		first_chara = player;
		next_chara = enemy;
	}
	else {
		first_chara = enemy;
		next_chara = player;
	}

	//�U���f�[�^�̍쐬
	first_attack_parameter = createAttackParameters(first_chara);
	next_attack_parameter = createAttackParameters(next_chara);
	
	//�h��f�[�^�̍쐬


	//�ǂ��炩��HP�������Ȃ�܂ő�����
	while (player->getDefaultStatus().hp > 0 && enemy->getDefaultStatus().hp > 0) {
		
	}
}

/// <summary>
/// ��U�����߂�
/// </summary>
/// <param name="_chara1">�L�����N�^�[1�̃p�����[�^</param>
/// <param name="_chara2">�L�����N�^�[2�̃p�����[�^</param>
/// <returns>
/// true : �L�����N�^�[1����U
/// false : �L�����N�^�[2����U
/// </returns>
bool BattleSystem::decideFirst(const CharaParameter& _chara1, const CharaParameter& _chara2) {
	return _chara1.speed >= _chara2.speed;
}

/// <summary>
/// �U���p�����[�^�̍쐬
/// </summary>
/// <param name="_chara">�L�����N�^�[</param>
/// <returns>
/// �U���p�����[�^
/// </returns>
std::vector<AttackParameter> BattleSystem::createAttackParameters(Character* _chara) {
	//�U���p�����[�^
	std::vector<AttackParameter> attackParameters;
	//�L�����N�^�[�̌��̔\��
	int chara_attack = _chara->getDefaultStatus().attack;
	int chara_critical = _chara->getDefaultStatus().critical;
	//�h��Œǉ����ꂽ�\��
	int add_attack = 0;
	int add_critical = 0;
	for (const auto& part : _chara->getParts()) {
		//�r�ȊO�̏ꍇ
		if (!part->getPartType().equal(part->getPartType())) {
			//�������Ă��Ȃ��Ȃ��΂�
			if (!part->isEquipping()) {
				continue;
			}
			//�S�U�����ʂ̃p�����[�^�ɉ�����
			add_attack += part->getEquipment()->getParameter().attack;
			add_critical += part->getEquipment()->getParameter().critical;
		}
		//�r�̏ꍇ
		else {
			//�p�����[�^��ǉ�����
			attackParameters.emplace_back(AttackParameter(chara_attack, chara_critical, part.get()));
		}
	}

	//�U�����ʂ��Ȃ��ꍇ�p�̍U���p�����[�^
	if (attackParameters.empty()) {
		attackParameters.emplace_back(AttackParameter(chara_attack, chara_critical));
	}

	//�S�U�����ʂ̃p�����[�^��������
	for (auto& attack_parameter : attackParameters) {
		attack_parameter.attack += add_attack;
		attack_parameter.critical += add_critical;
	}

	return attackParameters;
}

/// <summary>
/// �U������
/// </summary>
/// <param name="_attack_parameter">�U���p�����[�^</param>
/// <param name="_defence_parameter">�h��p�����[�^</param>
/// <returns>
/// �_���[�W
/// </returns>
int BattleSystem::attack(const std::vector<AttackParameter>& _attack_parameters, const DefenceParameter& _defence_parameter) {
	int total_damage = 0;
	for (const auto& attack : _attack_parameters) {
		bool is_good_type = false;
		bool is_bad_type = false;
		int total_defence;
		for (int i = 0; i < (int)Attribute::Num; ++i) {
			switch (AttributeChemistories[(int)attack.attributePower.attribute][i]) {
			case 0:
				total_defence += _defence_parameter.defence[i];
					break;
			case 1:
				is_good_type = true;
				total_defence += _defence_parameter.defence[i] / 2;
				break;
			case -1:
				is_bad_type = true;
				total_defence += _defence_parameter.defence[i] * 3 / 2;
				break;
			default:
				ErrorMessage("�����̑����ŕs���Ȓl���n����܂���");
				break;
			}
		}
		int fixed_attack = attack.attack;
		fixed_attack += attack.attributePower.power*(50 * (int)is_good_type - 50 * (int)is_bad_type + 100) / 100;
		int damage;
		//�U���͂��Ⴂ�ꍇ
		if (fixed_attack <= total_defence * 4 / 7) {
			damage = RandMt::GetRand(fixed_attack / 2 - total_defence / 4);
		}
		else {
			damage = fixed_attack / 2 - total_defence / 4;
			int random_damage = RandMt::GetRand(damage * 2) - damage + 1;
			damage += random_damage;
		}
		//�_���[�W��0�ȉ��Ȃ�C��
		if (damage <= 0) {
			damage = 1;
		}
		total_damage += damage;
	}
	return total_damage;
}
