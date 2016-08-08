class Stack
  def initialize
    self.contents = []
  end

  def push(thing)
    contents.push(thing)
  end

  def pop
    contents.pop
  end

  def to_s
    contents.to_s
  end

  private

  attr_accessor :contents
end

s = Stack.new

s.push(5)
s.push(3)
s.push(2)
s.pop
puts s
