#include "./core/buffer_object.h"

#include "./core/root_object.h"

namespace Splash
{

/**************/
void BufferObject::setNotUpdated()
{
    GraphObject::setNotUpdated();
    _updatedBuffer = false;
}

/*************/
bool BufferObject::deserialize()
{
    if (!_newSerializedObject)
        return false;

    bool returnValue = deserialize(_serializedObject);
    _newSerializedObject = false;

    return returnValue;
}

/*************/
void BufferObject::setSerializedObject(const std::shared_ptr<SerializedObject>& obj)
{
    if (_serializedObjectWaitingMutex.try_lock())
    {
        _serializedObject = obj;
        _newSerializedObject = true;

        // Deserialize it right away, in a separate thread
        _deserializeFuture = std::async(std::launch::async, [this]() {
            std::lock_guard<std::shared_mutex> lock(_writeMutex);
            deserialize();
            _serializedObjectWaitingMutex.unlock();
        });
    }
}

/*************/
void BufferObject::updateTimestamp(int64_t timestamp)
{
    std::lock_guard<Spinlock> lock(_timestampMutex);
    if (timestamp != -1)
        _timestamp = timestamp;
    else
        _timestamp = Timer::getTime();
    _updatedBuffer = true;
    if (_root)
        _root->signalBufferObjectUpdated();
}

/*************/
void BufferObject::registerAttributes()
{
    GraphObject::registerAttributes();
}

} // namespace Splash
