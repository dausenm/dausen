<?php
    class Calc{
        public $operator;
        public $num1;
        public $num2;


        public function __construct(string $op, int $number1, int $number2) {
            $this->operator = $op;
            $this->num1 = $number1;
            $this->num2 = $number2;
        }

        public function calculator() {
            switch($this->operator){
                case 'add':
                    $result = $this->num1 + $this->num2;
                    return $result;

                case 'sub':
                    $result = $this->num1 - $this->num2;
                    return $result;

                case 'div':
                    $result = $this->num1 / $this->num2;
                    return $result;

                case 'mul':
                    $result = $this->num1 * $this->num2;
                    return $result;

                default:
                    echo "Error!";
                break;
            }
        }
    }
?>