using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class MakePlayerController : MonoBehaviour
{
    private Gamepad gamepad;

    private bool fin = false;
    // Update is called once per frame
    void Update()
    {
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        if(gamepad.rightTrigger.ReadValue() > 0.8f && !fin)
        {
            gameObject.GetComponent<Animator>().SetTrigger("Attack");
            fin = true;
        }
    }

    void AttackFinish()
    {
        fin = false;
    }
}
