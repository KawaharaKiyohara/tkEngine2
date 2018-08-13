/*!
 * @brief	�S�[�X�g�I�u�W�F�N�g�B
 */

#pragma once


namespace tkEngine{
	/*!
	 * @brief	�S�[�X�g�I�u�W�F�N�g
	 *@detail
	 * �S�[�X�g�I�u�W�F�N�g�͍��̂����蔲���邠���蔻��̃I�u�W�F�N�g�ł��B
	 * �L�����N�^�[�̃`�F�b�N�|�C���g�ʉߔ���A�N���A����Ȃǂ�
	 * �L�����N�^�[�����蔲����K�v�̂��邠���蔻��Ɏg���܂��B
	 */
	class CPhysicsGhostObject{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CPhysicsGhostObject();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CPhysicsGhostObject	();
		/*!
		 * @brief	�{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 *@param[in]	size	�T�C�Y�B	
		 */
		void Create(CVector3 pos, CQuaternion rot, CVector3 size);
		/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release();
		/*!
		* @brief	�����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g���ǂ�������B
		*/
		bool IsSelf(const btCollisionObject& ghost) const
		{
			return &ghost == &m_ghostObject;
		}
		
	private:
		bool						m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
		btGhostObject				m_ghostObject;	//!<�S�[�X�g
		std::unique_ptr<ICollider>	m_collider;		//!<�R���C�_�[�B
	};
}