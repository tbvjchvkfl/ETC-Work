using System.Collections;
using UnityEngine;
using UnityEngine.InputSystem;

public class SpawnObject : MonoBehaviour
{
    public float MoveSpeed { get; set; } = 10.0f;
    public bool bIsInitializeSuccess { get; set; } = false;
    
    Rigidbody objectBody;
    BoxCollider clampMovingArea;

    Vector3 randomDirection = Vector3.zero;
    Vector3 movementLocation = Vector3.zero;

    //float decreaseDampingSpeed = 1.0f;

    void Update()
    {
        Debug.DrawLine(transform.position, transform.position + transform.forward * 10.0f, Color.red);
        if(objectBody.linearDamping > 0.0f)
        {
            Debug.Log(objectBody.linearDamping);
        }
        
    }

    void FixedUpdate()
    {
        Move();
    }

    public void InitializeObject()
    {
        objectBody = GetComponent<Rigidbody>();
        if (clampMovingArea = GameObject.FindGameObjectWithTag("Spawn Area").GetComponent<BoxCollider>())
        {

        }
        else
        {
            Debug.Log("Null");
        }
        float YAxisValue = Random.Range(-1.0f, 1.0f) > 0.0f ? 1.0f : -1.0f;
        randomDirection = new Vector3(Random.Range(-1.0f, 1.0f) * 90.0f, YAxisValue, 0.0f);
        transform.rotation = Quaternion.LookRotation(randomDirection);
    }

    public void MemorizeSpawnLocation(Vector3 SpawnLocation)
    {
        movementLocation = SpawnLocation;
    }

    public void InteractionObject(float Power, Vector3 mousePoint)
    {
        Debug.Log("Mouse is Moving");
        Vector3 RunDirection = transform.position - mousePoint;
        RunDirection.Normalize();
        objectBody.AddForce(RunDirection * Power, ForceMode.Impulse);
        transform.rotation = Quaternion.LookRotation(RunDirection);
    }

    public void Move()
    {
        if (bIsInitializeSuccess)
        {
            objectBody.MovePosition(objectBody.position + transform.forward * MoveSpeed * Time.deltaTime);
            Rotation();
        }
    }

    void Rotation()
    {

    }
}
