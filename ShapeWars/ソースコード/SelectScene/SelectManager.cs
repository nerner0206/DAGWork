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
    //  ゲームパッド
    private Gamepad gamepad;

    [SerializeField] private GameObject handle;
    [SerializeField] private List<GameObject> shapePrefabs;

    //  武器番号
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
        //  ゲームパッドを取得
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        //  メイクシーンへ
        if(gamepad.xButton.wasPressedThisFrame)
        {
            SceneManager.LoadScene("MakeScene");
        }
        //  プレイシーンへ
        if(gamepad.bButton.wasPressedThisFrame)
        {
            SceneManager.LoadScene("PlayScene");
        }

        //  番号を変える
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
