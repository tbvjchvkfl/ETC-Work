using System.Collections;
using UnityEngine;
using UnityEngine.InputSystem;

public class SpawnObject : MonoBehaviour
{
    public float MoveSpeed { get; set; } = 10.0f;
    public bool bIsInitializeSuccess { get; set; } = false;
    
    Rigidbody objectBody;
    BoxCollider clampMovingArea;

    Vector2 randomDirection = Vector2.zero;
    Vector3 movementLocation = Vector3.zero;

    float decreaseDampingSpeed = 1.0f;

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
        randomDirection = new Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)).normalized;
        transform.localRotation = Quaternion.Euler(randomDirection.x * 90.0f, randomDirection.y * 90.0f, 0);
    }

    public void MemorizeSpawnLocation(Vector3 SpawnLocation)
    {
        movementLocation = SpawnLocation;
    }

    public void InteractionObject(float Power)
    {
        if (Input.mousePositionDelta.magnitude > 0.1f)
        {
            Debug.Log("Mouse is Moing");
            Vector3.SignedAngle(Input.mousePosition, transform.forward, Vector3.up);
            Vector3.SignedAngle(Input.mousePosition, transform.forward, Vector3.right);
        }
        else
        {
            randomDirection = new Vector2(Random.Range(-1.0f, 1.0f), Random.Range(-1.0f, 1.0f)).normalized;
            transform.rotation = Quaternion.Euler(randomDirection.x * 90.0f, randomDirection.y * 90.0f, 0);
            objectBody.linearDamping = 10.0f;
            objectBody.AddForce(transform.forward * Power, ForceMode.Impulse);
            StartCoroutine(ResetDampingValue());
        }
        /*if (objectBody)
        {
            Vector3 RandomDirection = new Vector3(Random.Range(-1f, 1f), Random.Range(0f, 1f), Random.Range(-1f, 1f)).normalized;
            objectBody.AddForce(RandomDirection * Power, ForceMode.Impulse);
            Debug.Log("Object Interacted");
        }*/
    }

    IEnumerator ResetDampingValue()
    {
        while(objectBody.linearDamping > 0.0f)
        {
            objectBody.linearDamping -= decreaseDampingSpeed * Time.deltaTime;
            yield return null;
        }
        objectBody.linearDamping = 0.0f;
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
