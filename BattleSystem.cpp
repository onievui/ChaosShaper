#include "BattleSystem.h"
#include "LogSystem.h"
#include "ErrorMessage.h"
#include "RandMt.h"
#include <vector>
#include <sstream>
#include <iostream>



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
bool BattleSystem::battle() {
	LogSystem* log_system = LogSystem::getIns();
	Character* first_chara;
	Character* next_chara;

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
	std::vector<AttackParameter> first_attack_parameter;
	std::vector<AttackParameter> next_attack_parameter;
	first_attack_parameter = createAttackParameters(first_chara);
	next_attack_parameter = createAttackParameters(next_chara);
	
	//�h��f�[�^�̍쐬
	DefenceParameter first_defence_parameter = DefenceParameter(first_chara);
	DefenceParameter next_defence_parameter = DefenceParameter(next_chara);

	//�ǂ��炩��HP�������Ȃ�܂ő�����
	while (1) {
		log_system->addLog(first_chara->getName() + std::string("�̍U��"));
		Sleep(500);
		if (!dodge(next_chara->getStatus(), first_chara->getStatus())) {
			next_chara->damage(attack(first_attack_parameter, next_defence_parameter));
			next_chara->updateHp();
		}
		else {
			log_system->addLog(next_chara->getName() + std::string("�͍U�����������"));
		}
		Sleep(300);
		if (next_chara->getDefaultStatus().hp <= 0) {
			break;
		}

		log_system->addLog(next_chara->getName() + std::string("�̍U��"));
		Sleep(500);
		if (!dodge(first_chara->getStatus(), next_chara->getStatus())) {
			first_chara->damage(attack(next_attack_parameter, first_defence_parameter));
			first_chara->updateHp();
		}
		else {
			log_system->addLog(first_chara->getName() + std::string("�͍U�����������"));
		}
		Sleep(300);
		if (first_chara->getDefaultStatus().hp <= 0) {
			break;
		}
	}

	//�v���C���[�������̏ꍇ
	if (player->getDefaultStatus().hp <= 0) {
		log_system->addLog("�v���C���[�͎���ł��܂����c");
		Sleep(3000);
		return false;
	}
	//�v���C���[�������̏ꍇ
	else {
		log_system->addLog(enemy->getName() + std::string("��|�����I"));
		Sleep(2000);
		return true;
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
/// �U���̉�𔻒�
/// </summary>
/// <param name="_chara1">������L�����̃p�����[�^</param>
/// <param name="_chara2">�U������L�����̃p�����[�^</param>
/// <returns>
/// true : ���
/// false : ����
/// </returns>
bool BattleSystem::dodge(const CharaParameter& _chara1, const CharaParameter& _chara2) {
	int dodge_power = 100 * _chara1.speed / _chara2.speed;
	if (dodge_power < 50) {
		dodge_power = 49;
	}
	if (dodge_power >= 94) {
		dodge_power = 94;
	}
	if (dodge_power < (int)RandMt::GetRand(100)) {
		return true;
	}
	return false;
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
		int total_defence = 0;
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
		//�N���e�B�J������
		if (attack.critical > (int)RandMt::GetRand(100)) {
			LogSystem::getIns()->addLog("�N���e�B�J���I");
			fixed_attack = fixed_attack * 3 / 2 + 1;
		}
		int damage;
		//�U���͂��Ⴂ�ꍇ
		if (fixed_attack <= total_defence * 4 / 7) {
			damage = RandMt::GetRand(fixed_attack / 16);
		}
		else {
			damage = fixed_attack / 2 - total_defence / 4;
			int random_damage = RandMt::GetRand(damage / 8 + 1) - damage / 16 + 1;
			damage += random_damage;
		}
		//�_���[�W��0�ȉ��Ȃ�C��
		if (damage <= 0) {
			damage = 1;
		}
		total_damage += damage;
	}
	std::ostringstream oss;
	oss << total_damage << "�̃_���[�W";
	LogSystem::getIns()->addLog(oss.str());
	return total_damage;
}
