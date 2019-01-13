#include "PlayScene.h"
#include "ShareDataManager.h"
#include "Portion.h"
#include <iostream>


/// <summary>
/// �V�[���؂�ւ��C���^�t�F�[�X�̓o�^
/// </summary>
/// <param name="_impl">���X�i�[�ւ̃|�C���^</param>
PlayScene::PlayScene(RequestSceneListener* _impl) 
	: AbstractScene(_impl) {
	initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene() {
}

/// <summary>
/// �V�[���̏�����
/// </summary>
void PlayScene::initialize() {
	player = std::make_unique<Player>();
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
void PlayScene::update() {
	Player player = Player("ony");
	auto equip = std::make_unique<Equipment>("sword", 10, PartType::Arm, EquipParameter(), AttributePower(Attribute::Fire, 200));
	auto pot = std::make_unique<Portion>("pot", 10, 100);
	auto part = std::make_unique<Part>(PartType::Arm);
	player.addPart(std::move(part));
	player.addItem(std::move(equip));
	player.addItem(std::move(pot));

	std::cout << "name : " + player.getName() << std::endl;
	std::cout << std::endl;

	CharaParameter param = player.getStatus();
	std::cout << "level   : " << param.level << std::endl;
	std::cout << "hp      : " << param.hp << std::endl;
	std::cout << "attack  : " << param.attack << std::endl;
	std::cout << "defence : " << param.defence << std::endl;
	std::cout << std::endl;


	for (const auto& item : player.getItems()) {
		std::cout << item->getDetail() << std::endl;
	}
	std::cout << std::endl;

	for (const auto& part : player.getParts()) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;

	player.autoEquipping();

	for (const auto& part : player.getParts()) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;

	for (const auto& item : player.getItems()) {
		std::cout << item->getDetail() << std::endl;
	}
	std::cout << std::endl;

	player.removeEquipment(0);

	for (const auto& part : player.getParts()) {
		std::cout << part->getDetail() << std::endl;
	}
	std::cout << std::endl;

	for (const auto& item : player.getItems()) {
		std::cout << item->getDetail() << std::endl;
	}
	std::cout << std::endl;


	std::cin.get();
}


/// <summary>
/// �V�[���̕`��
/// </summary>
void PlayScene::render() {

}

/// <summary>
/// �V�[���̏I������
/// </summary>
void PlayScene::finalize() {

}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="_impl">�C���^�t�F�[�X�ւ̃|�C���^</param>
/// <returns>
/// �V�[���I�u�W�F�N�g
/// </returns>
std::unique_ptr<AbstractScene> PlayScene::create(RequestSceneListener* _impl) {
	return std::move(std::make_unique<PlayScene>(_impl));
}
