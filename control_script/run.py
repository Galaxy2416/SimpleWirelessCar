import pythoncom, pyHook

import serial
import serial.tools.list_ports


def OnKeyboardEventInfo(event):
    print ('MessageName:{}'.format(event.MessageName))
    print ('Message:{}'.format(event.Message))
    print ('Time:{}'.format(event.Time))
    print ('Window:{}'.format(event.Window))
    print ('WindowName:{}'.format(event.WindowName))
    print ('Ascii:{} {}'.format(event.Ascii, chr(event.Ascii)))
    print ('Key:{}'.format(event.Key))
    print ('KeyID:{}'.format(event.KeyID))
    print ('ScanCode:{}'.format(event.ScanCode))
    print ('Extended:{}'.format(event.Extended))
    print ('Injected:{}'.format(event.Injected))
    print ('Alt:{}'.format(event.Alt))
    print ('Transition:{}'.format(event.Transition))
    print ('---')

# return True to pass the event to other handlers
    return True


class serialSender:

    ser = 0

    keyup = 38
    keydown = 40
    keyleft = 37
    keyright = 39
    key_w = 87
    key_s = 83
    key_a = 65
    key_d = 68
    

    key_dir = {keyup : 7, keydown : 6, keyleft : 5, keyright : 4, key_w : 3, key_s : 2, key_a : 1, key_d : 0}

    cmd = 0

    status_list = [False,False,False,False,False,False,False,False] # up down left right w s a d

    def __init__(self):
        print('I\'m the tool to send the command to the car. ' )
    def __del__( self ):
        print('Close the sender tool.')
        self.close_the_serial();
    
    def conncet_to_serial(self, com_name, com_num = 9600):
        self.ser = serial.Serial(com_name, com_num, timeout = 60)
    def connect_to_serial(self):
        vid_pid = '10C4:EA60'
        # connect to com auto
        port_list = list(serial.tools.list_ports.comports())
        if len(port_list) <= 0:
            print ("The Serial port can't find!")
        else:
            for i in port_list:
                if str(list(i)[2]).find(vid_pid) != -1 : # VID:PID = XXXX:XXXX
                    port_list_use =list(i)
                    port_serial = port_list_use[0]
                    self.ser = serial.Serial(port_serial,9600, timeout = 60)
                    print ("Find the port >", self.ser)
                    break
            if self.ser == 0:
                print("Cannot find the port of wireless serial.")

    def close_the_serial(self):
        if self.ser != 0:
            self.ser.close();

    def get_the_cmd(self,cmd):
        cmd = 0;
        for i in self.status_list:
            cmd = cmd << 1
            if i :
                cmd =  cmd | 0x01
        return cmd
                
            
    def OnKeyboardEventDown(self,event):
        if event.KeyID in self.key_dir:
            self.status_list[self.key_dir[event.KeyID]] = True;
            OnKeyboardEventInfo(event)
        cmd = self.get_the_cmd(self.cmd)
        if cmd != self.cmd:
            self.cmd = cmd;
            self.ser.write(chr(self.cmd).encode())
           # print self.cmd 
            
        return True
    
    def OnKeyboardEventUp(self,event):
        if event.KeyID in self.key_dir:
            self.status_list[self.key_dir[event.KeyID]] = False;
            OnKeyboardEventInfo(event)
        self.cmd = self.get_the_cmd(self.cmd)
        self.ser.write(chr(self.cmd).encode())
        # print self.cmd 
            
        return True 


if __name__ == '__main__':
    print('starting...')
    #  sender   
    ss = serialSender()
    ss.connect_to_serial()
    # create a hook manager
    hm = pyHook.HookManager()
    # watch for all mouse events
    # hm.KeyAll = OnKeyboardEvent
    hm.SubscribeKeyDown(ss.OnKeyboardEventDown)
    hm.SubscribeKeyUp(ss.OnKeyboardEventUp)


    # set the hook
    hm.HookKeyboard()
    # wait forever
    pythoncom.PumpMessages()
