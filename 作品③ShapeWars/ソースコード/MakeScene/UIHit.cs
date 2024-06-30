using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIHit : MonoBehaviour
{
    //  �q�b�g���Ă���
    public bool hit;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("MoveIcon")) hit = true;
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.CompareTag("MoveIcon")) hit = false;
    }
}
