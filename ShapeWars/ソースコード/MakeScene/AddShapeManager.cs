using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;

public class Weapon
{
    public int animID;
    public int[] ID;
    public Vector3[] pos;
    public Vector3[] rot;
    public Vector3[] sca;
}

public class AddShapeManager : MonoBehaviour
{
    //  �e�̃n���h���I�u�W�F�N�g
    [SerializeField] private GameObject handleObject;
    [SerializeField] private GameObject handlePrefab;

    //  �ǉ�����I�u�W�F�N�g
    public List<GameObject> shapePrefabs;

    //  �Z�[�u�p�̃N���X�ϐ�
    Weapon weapon = new Weapon();

    //  �}�`�𐶐�����
    public GameObject AddShape(int num)
    {
        //  ��������
        GameObject part = Instantiate(shapePrefabs[num], Vector3.zero, Quaternion.identity);
        //  �q�I�u�W�F�N�g�ɂ���
        part.transform.parent = handleObject.transform;
        //  �}�`�ԍ�������
        part.GetComponent<ObjectData>().num = num;

        return part;
    }

    //  �Z�[�u����
    public void Save(int num, int animNum)
    {
        //  �N���X�Ɋi�[����
        //  ���i���i�[(�����̏����͏d��)
        GameObject[] weaponParts = GameObject.FindGameObjectsWithTag("WeaponPart");

        //  �N���X��������
        weapon = new Weapon();
        //  �A�j���[�V�����ԍ�
        weapon.animID = animNum;

        //  �������I�u�W�F�N�g�̔ԍ����擾
        if(weaponParts != null)
        {
            weapon.ID = new int[weaponParts.Length];
            weapon.pos = new Vector3[weaponParts.Length];
            weapon.rot = new Vector3[weaponParts.Length];
            weapon.sca = new Vector3[weaponParts.Length];

            for (int i = 0; i < weaponParts.Length; i++)
            {
                weapon.ID[i] = weaponParts[i].GetComponent<ObjectData>().num;
                weapon.pos[i] = weaponParts[i].transform.position;
                weapon.rot[i] = weaponParts[i].transform.eulerAngles;
                weapon.sca[i] = weaponParts[i].transform.localScale;
            }

        }

        // ToJson���\�b�h�̑�Q�����́A���₷���t�H�[�}�b�g����X�C�b�`�ł�
        string jsonString = JsonUtility.ToJson(weapon, true);
        // JSON�f�[�^���t�@�C���ɕۑ�
        File.WriteAllText(Initialize.dataPathes[num], jsonString);
    }
}
