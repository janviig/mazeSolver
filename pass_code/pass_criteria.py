import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class ScaredRobot(Node):

    def front_listener_callback(self, msg):
        print(msg.data)
        
        front = int(msg.data[:-2]) #remove the 'cm' and convert to int.

        if front < 20 and front > 10:
            msg = String()
            msg.data = "CONTF:0200\n" 
            self.publisher.publish(msg)
        if front < 10:
            msg = String()
            msg.data = "TURNR:0100\n"
            self.publisher.publish(msg)
        else:
            msg = String()
            msg.data = "MOVEF:0100\n"
            self.publisher.publish(msg)

    def left_listener_callback(self, msg):
        print(msg.data)

        left = int(msg.data[:-2]) #remove the 'cm' and convert to int.

        if left < 20:
            msg = String()
            msg.data = "TURNR:0100\n"
            self.publisher.publish(msg)

    def right_listener_callback(self, msg):
        print(msg.data)

        right = int(msg.data[:-2])  # remove the 'cm' and convert to int.

        if right < 20:
            msg = String()
            msg.data = "TURNL:0100\n"
            self.publisher.publish(msg)
       

    def __init__(self):
        super().__init__('ScaredRobot')
        self.publisher = self.create_publisher(String, '/robot/control', 10)

        self.subscription = self.create_subscription(
            String,
            '/robot/front',
            self.front_listener_callback,
            1)
        self.subscription  # prevent unused variable warning

        self.subscription = self.create_subscription(
            String,
            '/robot/left',
            self.left_listener_callback,
            1)
    
        self.subscription = self.create_subscription(
            String,
            '/robot/right',
            self.right_listener_callback,
            1)

def main(args=None):
    rclpy.init(args=args)

    scaredrobot = ScaredRobot()
    rclpy.spin(scaredrobot)
    
    scaredrobot.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

