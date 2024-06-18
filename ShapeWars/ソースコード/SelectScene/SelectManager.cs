using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;
using System;
using System.IO;

public class SelectManager : MonoBehaviour
{
    //  �Q�[���p�b�h
    private Gamepad gamepad;

    [SerializeField] private GameObject handle;
    [SerializeField] private List<GameObject> shapePrefabs;

    //  ����ԍ�
    public static int weaponDataNumber = 0;

    [SerializeField] private Text numText;

    // Start is called before the first frame update
    private void Start()
    {
        Debug.Log(Initialize.dataPathes[0]);
        Debug.Log(Initialize.dataPathes[1]);
        Debug.Log(Initialize.dataPathes[2]);
        Debug.Log(Initialize.dataPathes[3]);
        Debug.Log(Initialize.dataPathes[4]);
    }
    private void Update()
    {
        //  �Q�[���p�b�h���擾
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        //  ���C�N�V�[����
        if(gamepad.xButton.wasPressedThisFrame)
        {
            SceneManager.LoadScene("MakeScene");
        }
        //  �v���C�V�[����
        if(gamepad.bButton.wasPressedThisFrame)
        {
            SceneManager.LoadScene("PlayScene");
        }

        //  �ԍ���ς���
        if(gamepad.dpad.up.wasPressedThisFrame && weaponDataNumber > 0)
        {
            weaponDataNumber--;
        }
        else if(gamepad.dpad.down.wasPressedThisFrame && weaponDataNumber < 5)
        {
            weaponDataNumber++;
        }

        numText.text = weaponDataNumber.ToString();
    }
}
