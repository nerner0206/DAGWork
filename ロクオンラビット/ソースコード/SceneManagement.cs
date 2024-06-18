using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum AllScene
{
    LogoScene,
    TitleScene,
    SelectScene,
    PlayScene,
};

public class SceneManagement : MonoBehaviour
{
    [SerializeField, Header("���̃V�[�����")]
    protected string[] m_nextSceneNames;
    [SerializeField, Header("�t�F�C�h�^�C��")]
    protected float m_fadeTime = 1.0f;
    [SerializeField, Tooltip("�I�v�V����")]
    protected GameObject m_optionPrefab;

    //  �I�v�V�������J���锻��̎擾
    public virtual bool NonOptionState() { return false; }
}
