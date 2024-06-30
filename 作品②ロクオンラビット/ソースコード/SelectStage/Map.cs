using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(SpriteRenderer))]
public class Map : MonoBehaviour
{
    [SerializeField, Tooltip("�f�t�H���g�}�e���A��")]
    private Material m_defMaterial;
    [SerializeField, Tooltip("�A�E�g���C���}�e���A��")]
    private Material m_outLineMaterial;
    [SerializeField, Tooltip("SpriteRenderer")]
    private SpriteRenderer m_spriteRenderer;

    //  �A�C�R�����}�b�v��ɂ���
    public void SetOnIcon()
    {
        //  �A�E�g���C���}�e���A���ɕύX
        m_spriteRenderer.material = m_outLineMaterial;
    }
    //  �A�C�R�����}�b�v��ɂȂ�
    public void SetRemoveIcon()
    {
        //  �m�[�}���̃}�e���A���ɖ߂�
        m_spriteRenderer.material = m_defMaterial;
    }
}
