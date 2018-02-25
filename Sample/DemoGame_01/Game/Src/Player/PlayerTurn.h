/*!
 * @brief	�v���C���[�̐��񏈗��B
 */

#pragma once

class CPlayer;

class CPlayerTurn : public IGameObject{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CPlayerTurn(CPlayer* pl) :
		m_player(pl)
	{
	}
	/*!
	 * @brief	�X�V�B
	 */
	void Update() override final;
private:
	CPlayer* m_player = nullptr;
};