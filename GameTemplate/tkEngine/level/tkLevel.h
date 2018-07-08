/*!
 *@brief	���x���B
 */

#pragma once

namespace tkEngine{
	class CMapChip;
	/*!
	* @brief	�I�u�W�F�N�g���B
	*/
	struct LevelObjectData {
		CVector3 position;		//<���W�B
		CQuaternion rotation;	//!<��]�B
		const wchar_t* name;	//!<���O�B
	};
	/*!
	 *@brief	���x���B
	 */
	class CLevel : Noncopyable{
	public:
		/*!
		 * @brief	���x�����������B
		 *@param[in]	levelDataFilePath		tkl�t�@�C���̃t�@�C���p�X�B
		 *@param[in] hookFunc				�I�u�W�F�N�g���쐬���鎞�̏������t�b�N���邽�߂̊֐��I�u�W�F�N�g�B
		 *   �t�b�N���Ȃ��Ȃ�nullptr���w�肷��΂悢�A
		 * ���̊֐��I�u�W�F�N�g��false��Ԃ��ƁA�I�u�W�F�N�g�̏�񂩂�A
		 * �ÓI�I�u�W�F�N�g��MapChip�N���X�̃C���X�^���X����������܂��B
		 * �I�u�W�F�N�g�̖��O�ȂǂŁA�h�A��W�����v��A�A�C�e���Ȃǂ̓���ȃN���X�̃C���X�^���X�𐶐������Ƃ��ɁA
		 * �f�t�H���g�ō쐬�����MapChip�N���X�̃C���X�^���X���s�v�ȏꍇ��true��Ԃ��Ă��������B
		 * �Ⴆ�΁A�t�b�N�֐��̒��ŁA�n���ꂽ�I�u�W�F�N�g�f�[�^�̖��O�̃��f����`�悷��N���X�̃C���X�^���X��
		 * ���������Ƃ��ɁAfalse��Ԃ��Ă��܂��ƁA�������f������`�悳��邱�ƂɂȂ�܂��B
		 */
		void Init( const wchar_t* filePath,  std::function<bool(LevelObjectData& objData)> hookFunc);
	private:
		using CMapChipPtr = std::unique_ptr<CMapChip>;
		std::vector<CMapChipPtr>	m_mapChipPtr;		//�}�b�v�`�b�v�̉ϒ��z��B
	};
}